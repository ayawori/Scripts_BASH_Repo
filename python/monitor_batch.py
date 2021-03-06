#!/usr/bin/env python
# -*- coding: utf-8 -*-

from pyModbusTCP.client import ModbusClient
import time
import struct
import datetime
import csv
import random

import extmod  # updated modbus library that handles floats/doubles/text
import accuload

print(pyModbusTCP.__file__)

LOGFILE     = "test.csv"
SERVER_HOST = "192.168.76.1"
SERVER_PORT = 502

# c = extmod.ExtendedModbusClient(host=SERVER_HOST, port=SERVER_PORT, auto_open=True)
c = accuload.Connect(host=SERVER_HOST, port=SERVER_PORT)
EndBatch(c)

# Check for alarms from possible previous run, stop if encountered 
status = c.read_discrete_inputs(4160, 17)
if status[8]:
    print("Alarms are present...check AccuLoad.")
    exit() 

# 0x0400 AB variant, allocate recipe 7 for the batch
command = c.write_multiple_registers(0, [12, 0x0400, 2, 0, 64, 0, 0]) 
update = c.write_single_coil(4096,1)
AB_result = c.read_input_registers(0, 4)
print("Allocated Recipe 7..." + str(hex(AB_result[2])))


# c = ConnectUUT(host, port, auto_open)
# AllocateBatch(object=c, mask=<0x000>)

# 0x0400 SB variant, preset batch to 990-1010 gallons
RAND_PRESET_VOL  = round(random.uniform(500.0, 1500.0), 0)   # Random preset from 900-1100
#  RAND_PRESET_VOL = 1000.0

# Issue Command Data
command = c.write_multiple_registers(0, [12, 0x0400, 3])
command = c.write_float(3, [RAND_PRESET_VOL])
command = c.write_single_register(5, 0xFFFF)
command = c.write_single_register(6, 0xFFFF)
update = c.write_single_coil(4096,1)
SB_result = c.read_input_registers(0, 4)
print("Setting batch volumes..." + str(hex(SB_result[2])))

# 0x0400 SA variant, start batch...
command = c.write_multiple_registers(0, [4, 0x0400, 6])
update = c.write_single_coil(4096,1)
SA_result = c.read_input_registers(0, 4)
print("Starting Batch..." + str(hex(SA_result[2])))

# StartBatch(var1, var2)...

time.sleep(1)
print("Running Batch...")

# Enter polling loop to monitor injectors, break when batch is done...
while True:
    # open or reconnect TCP to server
    if not c.is_open():
        if not c.open():
            print("unable to connect to "+SERVER_HOST+":"+str(SERVER_PORT))
            exit()

    # if open() is ok, read registers 
    if c.is_open():
        # read Transaction Status Flags (watching for batch running/done, alarms, etc.)
        # [2]=TP, [3]=BD, [4]=TD, [8]=AL, [12]=FL
        status      = c.read_discrete_inputs(4160, 17)
        AL3time     = c.read_text(3, 3728, 16)

        trans_no    = round(int((c.read_input_registers(4864,1))[0]),0)
        batch_no    = round(int((c.read_input_registers(7683,1))[0]),0)
        recipe_no   = round(int((c.read_input_registers(7681,1))[0]),0)
        preset_vol  = round(float((c.read_float(4, 4364, 1))[0]),2)
        trans_GV    = round(float((c.read_double(4, 4484, 1))[0]),2)

        add5_volinj = round(float((c.read_float(4, 3128, 1))[0]),2)
        add5_curinj = round(int((c.read_input_registers(3652, 1))[0]),0)
        add5_rate   = round(float((c.read_float(4, 3080, 1))[0]),1)
        add5_vol    = round(float((c.read_double(4, 4520, 1))[0]),3)

        # Set/Get some parameters to determine ranges on batch later
        add_inj_stop_vol    = round(float((c.read_float(3, 4050, 1))[0]), 2)        # Additive Stop Volume (SYS 804)
        conv_factor         = round(float((c.read_float(3, 4052, 1))[0]), 3)        # Converstion factor (SYS 807)
        rec_add5_inj_amt    = round(float((c.read_float(3, 10824, 1))[0]), 2)       # Recipe Inj #5 Injection amt (REC 07 - 029)
        rec_add5_rate       = round(float((c.read_float(3, 10872, 1))[0]), 2)       # Recipe Inj #5 Rate (REC 07 - 030)
        rec_1st_pct         = round(float((c.read_float(3, 10976, 1))[0]), 2)       # Prd1 Percent of Recipe 7
        rec_2nd_pct         = round(float((c.read_float(3, 10978, 1))[0]), 2)       # Prd2 Percent of Recipe 7

        pacing_vol = preset_vol - add_inj_stop_vol
        calc_add_rate = round((rec_add5_rate*pacing_vol)/preset_vol, 1)
        tdiv = round((pacing_vol/rec_add5_rate)*(rec_add5_inj_amt/conv_factor), 3)

        # check for alarms, if any, bail and notify user
        if status[8]:
            print("ALARM occurred...check AccuLoad.")
            break

        # check for BD flag and NOT FL flag to then break to end transaction
        if (status[3] and not status[12]):
            print("Batch Done...")
            break

        # log the polling into a CSV file for later (appending)
        with open(LOGFILE, 'a') as inj_data:
            inj_data_writer = csv.writer(inj_data)
            inj_data_writer.writerow([AL3time[0:11], trans_no, batch_no, recipe_no, " ", preset_vol, trans_GV, add5_curinj, " ", add5_rate, calc_add_rate, " ", tdiv, add5_vol])
        inj_data.close()

        # check to see if the calculated additive rate doesn't match with expected rate
        # and alarm to bail out of testing loops...
        #if calc_add_rate != add5_rate:
        if abs(calc_add_rate - add5_rate) > 2.0:
            alarm = c.write_single_register(2112, 1)
            print("U1: Add5 Rate Change alarm present")
            print("Current Additive rate: " + str(add5_rate) + " Calc Additive rate: " + str(calc_add_rate))
            break
      

    # sleep 0.5s before next polling
    time.sleep(0.5)

# 0x0400 EB variant, end batch...
command = c.write_multiple_registers(0, [4, 0x0400, 4])
update = c.write_single_coil(4096,1)
EB_result = c.read_input_registers(0, 4)
print("Ending Batch..." + str(hex(EB_result[2])))

# 0x0400 ET variant, end transaction...
command = c.write_multiple_registers(0, [4, 0x0400, 5])
update = c.write_single_coil(4096,1)
ET_result = c.read_input_registers(0, 4)
print("Ending Transaction..." + str(hex(ET_result[2])))
