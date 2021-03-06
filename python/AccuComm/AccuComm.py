#!/usr/python

import sys
import os
import serial
import time
import glob
import socket
import commands
import AICB
import Macro

from PySide.QtGui import *
from PySide.QtCore import *
from AccuCommUI import Ui_MainWindow

PROTOCOLS_SERIAL = [
"Smithcomm Mini Host",
"Smithcomm Term Host",
"Modbus",
"Titan",
"Mini/Blend Pack",
"AICB",
"Terminal \\r\\n",
"Terminal \\n",
"Printer"
]

PROTOCOLS_TCP = [
"Smithcomm Mini Host",
"Smithcomm Term Host",
"Modbus",
"A4I",
"Tiva Command",
"Tiva Meter Injector",
"Raw"
]

BAUD = [
"1200",
"2400",
"5800",
"9600",
"19200",
"38400",
"115200"
]

STX = 0x02
ETX = 0x03
PAD = 0x7F

TIVA_UNLOCK_CODE = "=q)!%FP';/.$5owsAF+S"

class ParseState:
	FIND_NULL = 1,
	FIND_STX = 2,
	FIND_ETX = 3,
	FIND_PAD = 4,
	FIND_ASTR = 5,
	FIND_CRLF = 6,
	FIND_PREAMBLE = 7,
	FIND_TYPE = 8,
	FIND_INSTANCE = 9,
	FIND_LENGTH = 10,
	FIND_PAYLOAD = 11,
	IGNORE = 12,
	DONE = 13,
	FAILED = 14

class SerialThread(QThread):
	updateText = Signal(bytearray, str, int)

	def __init__(self, args = None):
		super(SerialThread, self).__init__()
		self.stopFlag = False
		if args is not None:
			self.port = args[0]
			self.protocol = args[1]

	def stop(self):
		self.stopFlag = True
		print "Stopping Thread"
	
	def stopped(self):
		return self.stopFlag

	def running(self):
		return self.isRunning

	def run(self):
		self.isRunning = True
		self.port.timeout = 0
		totalBytes = 0
		i = -1
		recv_bytes = bytearray()
		state = 0

		while 1:
			if self.protocol.currentText() == "Smithcomm Mini Host" or self.protocol.currentText() == "AICB":
				bytes_available = self.port.inWaiting()
				if bytes_available > 0:
					recv_bytes.extend(self.port.read(self.port.inWaiting()))
					if len(recv_bytes) > 0:		
						i = -1

						if self.protocol.currentText() == "Smithcomm Mini Host":
							state = ParseState.FIND_NULL
						else:
							state = ParseState.FIND_STX
						#Check the Protocol
						while i < (len(recv_bytes) - 1):
							i += 1

							if len(recv_bytes) >= 20000:
								state = ParseState.FIND_NULL
								recv_bytes = bytearray()
								print"Tooooooooooo Much Dataaaaaaaaaaaa"
								break


							if state == ParseState.FIND_NULL:
								if recv_bytes[i] == 0x00:
									state = ParseState.FIND_STX
									continue

							if state == ParseState.FIND_STX:
								if recv_bytes[i] == 0x02:
									state = ParseState.FIND_ETX
									startText = i + 1
									continue

							if state == ParseState.FIND_ETX:
								if recv_bytes[i] == 0x03:
									#Are We Waiting on the Recv?
									if i < (len(recv_bytes) - 1):
										lrc = 0
										recvLrc = recv_bytes[i+1]

										for j in recv_bytes[startText:(i+1)]:
											lrc ^= j

										if lrc == recvLrc:
											state = ParseState.DONE
											endText = i
										else:
											#Parse Failure
											state = ParseState.FAILED
											break
									else:
										continue

				
					if state == ParseState.DONE:
						if(str(recv_bytes[startText + 2:endText]) in commands.smith_errors):
							self.updateText.emit(recv_bytes[startText - 1:endText + 2], str(recv_bytes[startText:endText]) + "(" + commands.smith_errors[str(recv_bytes[startText + 2:endText])] + ")" + "\n", (endText + 2) - (startText - 1))
						else:
							self.updateText.emit(recv_bytes[startText - 1:endText + 2], str(recv_bytes[startText:endText]) + "\n", (endText + 2) - (startText - 1))

						i = -1
						recv_bytes = bytearray()

						if self.protocol.currentText() == "Smithcomm Mini Host":
							state = ParseState.FIND_NULL
						else:
							state = ParseState.FIND_STX
							totalBytes = 0

					if state == ParseState.FAILED:
						i = -1	
						recv_bytes = bytearray()

						if self.protocol.currentText() == "Smithcomm Mini Host":
							state = ParseState.FIND_NULL
						else:
							state = ParseState.FIND_STX
							totalBytes = 0
		
		
			elif self.protocol.currentText() == "Smithcomm Term Host":
				bytes_available = self.port.inWaiting()
				if bytes_available > 0:
					recv_bytes.extend(self.port.read(self.port.inWaiting()))
					if len(recv_bytes) > 0:		
						i = -1
						state = ParseState.FIND_ASTR
						#Check the Protocol
						while i < (len(recv_bytes) - 1):
							i += 1
							if len(recv_bytes) >= 20000:
								state = ParseState.FIND_ASTR
								recv_bytes = bytearray()
								print"Tooooooooooo Much Dataaaaaaaaaaaa"
								break

							if state == ParseState.FIND_ASTR:
								if recv_bytes[i] == 0x2A:
									state = ParseState.FIND_CRLF
									startText = i + 1
									continue

							if state == ParseState.FIND_CRLF:
								if recv_bytes[i] == 0x0D:
									#Are We Waiting on the Recv?
									if i < (len(recv_bytes) - 1):
										if recv_bytes[i+1] == 0x0A:
											state = ParseState.DONE
											endText = i
											break
										else:
											#Parse Failure
											endText = i
											state = ParseState.FAILED
											break
									else:
										continue
				
					if state == ParseState.DONE:
						if(str(recv_bytes[startText + 2:endText]) in commands.smith_errors):
							self.updateText.emit(recv_bytes[startText - 1:endText + 2], str(recv_bytes[startText:endText]) + "(" + commands.smith_errors[str(recv_bytes[startText + 2:endText])] + ")" + "\n", (endText + 2) - (startText - 1))
						else:
							self.updateText.emit(recv_bytes[startText - 1:endText + 2], str(recv_bytes[startText:endText]) + "\n", (endText + 2) - (startText - 1))

						state = ParseState.FIND_ASTR
						i = -1
						recv_bytes = bytearray()
						totalBytes = 0
						state = ParseState.FIND_ASTR

					if state == ParseState.FAILED:
						totalBytes = 0
						recv_bytes = bytearray()
						state = ParseState.FIND_ASTR
						currentResponse
						i = -1	
						state = state = ParseState.FIND_ASTR		

			elif self.protocol.currentText() == "Modbus":
				bytes_available = 0
			elif self.protocol.currentText() == "Titan":
				print "Titan"
			elif self.protocol.currentText() == "Mini/Blend Pack":
				print "Blend"

			elif self.protocol.currentText() == "Terminal \\r\\n":
				bytes_available = self.port.inWaiting()
				if bytes_available > 0:

					recv_bytes.extend(self.port.read(bytes_available))
					self.updateText.emit(recv_bytes,  str(recv_bytes[:bytes_available - 2] + "\n"),bytes_available)
					
			elif self.protocol.currentText() == "Terminal \\n":
				bytes_available = self.port.inWaiting()
				if bytes_available > 0:
					recv_bytes.extend(self.port.read(bytes_available))
					self.updateText.emit(recv_bytes, str(recv_bytes[:bytes_available - 1] + "\n"), bytes_available)

			elif self.protocol.currentText() == "Printer":
				bytes_available = self.port.inWaiting()
				if bytes_available > 0:
					recv_bytes.extend(self.port.read(bytes_available))
					self.updateText.emit(recv_bytes, str(recv_bytes), bytes_available)


			if self.stopFlag:
				self.isRunning = False
				print "Exiting"
				return

			time.sleep(0.001)

class TCPThread(QThread):
	updateText = Signal(bytearray, str, int)

	def __init__(self, args = None):
		super(TCPThread, self).__init__()
		self.stopFlag = False
		if args is not None:
			self.port = args[0]
			self.protocol = args[1]

	def stop(self):
		self.stopFlag = True
		print "Stopping Thread"
	
	def stopped(self):
		return self.stopFlag

	def running(self):
		return self.isRunning

	def run(self):
		self.isRunning = True
		state = state = ParseState.FIND_NULL
		totalBytes = 0
		nbytes = 0
		recv_bytes = bytearray()
		while 1:
			new_bytes = bytearray()
			if self.protocol.currentText() == "Smithcomm Mini Host":

				try:
					nbytes = 0
					new_bytes = self.port.recv(10000)
				except socket.timeout:
					pass
				except socket.error:
					print "Socket Error"
					return

				if len(new_bytes) > 0:	
					totalBytes += len(new_bytes)
					recv_bytes.extend(new_bytes)

					if totalBytes > 0:		

						state = ParseState.FIND_NULL
						i = 0
						#Check the Protocol
						while i < totalBytes:
							if totalBytes >= 50000:
								print "Tooooooooooo Much Dataaaaaaaaaaaa"

								state = 0
								recv_bytes = bytearray(50000)
								totalBytes = 0
								break

							if state == ParseState.FIND_NULL:
								if recv_bytes[i] == 0x00:
									state = ParseState.FIND_STX
									i += 1
									continue

							if state == ParseState.FIND_STX:
								if recv_bytes[i] == 0x02:
									state = ParseState.FIND_ETX
									startText = i + 1
									i += 1
									continue

							if state == ParseState.FIND_ETX:
								if recv_bytes[i] == 0x03:
									#Are We Waiting on the Recv?
									if i < (totalBytes - 1):
										lrc = 0
										recvLrc = recv_bytes[i+1]

										for j in recv_bytes[startText:(i+1)]:
											lrc ^= j

										if lrc == recvLrc:
											state = ParseState.DONE
											endText = i
										else:
											#Parse Failure
											state = ParseState.FAILED
											endText = i
											print "LRC Failure"
											break
									else:
										i += 1
										continue

							i += 1
				
				if state == ParseState.DONE:
					if(str(recv_bytes[startText + 2:endText]) in commands.smith_errors):
						self.updateText.emit(recv_bytes[startText - 1:endText + 2], str(recv_bytes[startText:endText]) + "(" + commands.smith_errors[str(recv_bytes[startText + 2:endText])] + ")" + "\n", (endText + 2) - (startText - 1))
					else:
						self.updateText.emit(recv_bytes[startText - 1:endText + 2], str(recv_bytes[startText:endText]) + "\n", (endText + 2) - (startText - 1))

					state = state = ParseState.FIND_NULL
					totalBytes = 0
					nbytes = 0
					recv_bytes = bytearray()


				elif state == ParseState.FAILED:
					state = state = ParseState.FIND_NULL
					totalBytes = 0
					nbytes = 0
					recv_bytes = bytearray()
	
			elif self.protocol.currentText() == "Smithcomm Term Host":
				
				try:
					nbytes = 0
					nbytes = self.port.recv_into(recv_bytes)
				except socket.timeout:
					pass
				except socket.error:
					print "Socket Error"
					return

				totalBytes += nbytes

				if totalBytes > 0:
					i = -1
					state = ParseState.FIND_ASTR
					#Check the Protocol
					while i < totalBytes:
						i += 1

						if totalBytes >= 50000:
							state = 0
							totalBytes = 0
							recv_bytes = bytearray()
							print"Tooooooooooo Much Dataaaaaaaaaaaa"
							break


						if state == ParseState.FIND_ASTR:
							if recv_bytes[i] == 0x2A:
								state = ParseState.FIND_CRLF
								startText = i + 1
								continue

						if state == ParseState.FIND_CRLF:
							if recv_bytes[i] == 0x0D:
								#Are We Waiting on the Recv?
								if i < (totalBytes - 1):
									if recv_bytes[i+1] == 0x0A:
										state = ParseState.DONE
										endText = i - 2
										break
									else:
										#Parse Failure
										endText = i - 2
										state = ParseState.FAILED
										break
								else:
									continue
				
				if state == ParseState.DONE:
					if(str(recv_bytes[startText + 2:endText]) in commands.smith_errors):
						self.updateText.emit(recv_bytes[startText - 1:endText + 2], str(recv_bytes[startText:endText]) + "(" + commands.smith_errors[str(recv_bytes[startText + 2:endText])] + ")" + "\n", (endText + 2) - (startText - 1))
					else:
						self.updateText.emit(recv_bytes[startText - 1:endText + 2], str(recv_bytes[startText:endText]) + "\n", (endText + 2) - (startText - 1))


					state = ParseState.FIND_ASTR
					totalBytes -= (endText + 2) - (startText - 1)
					recv_bytes = recv_bytes[endText+2:]
				elif state == ParseState.FAILED:
					state = ParseState.FIND_ASTR
					totalBytes -= (endText + 2) - (startText - 1)
					recv_bytes = recv_bytes[endText+2:]

			elif self.protocol.currentText() == "Modbus":
				self.updateText.emit(recv_bytes, str(recv_bytes) + "\n", len(recv_bytes))
				totalBytes = 0
			elif self.protocol.currentText() == "Titan":
				print "Titan"
			elif self.protocol.currentText() == "Mini/Blend Pack":
				print "Blend"
			elif self.protocol.currentText() == "AICB":
				print "AICB"
			elif self.protocol.currentText() == "Raw \\r\\n":
				print "Raw"

			if self.stopFlag:
				self.isRunning = False
				print "Exiting"
				return


#Serial Ports
if os.name is 'nt':
	ports = ['COM%s' % (i + 1) for i in range(256)]
elif os.name is 'posix':
	ports = glob.glob('/dev/tty[A-Za-z]*')

class MainWindow(QMainWindow, Ui_MainWindow):
	#Class Variables
	currentSerial = None
	foundReturn = False
	foundTxReturn = False

	#Slots
	@Slot()
	def MacroChange(self):
		self.macro_state = self.macro_checkbox.checkState()
		if self.macro_state:
			self.test_combo.setEnabled(False)
			self.command_line.setEnabled(False)
		else:
			self.test_combo.setEnabled(True)
			self.command_line.setEnabled(True)
	@Slot()
	def OpenFile(self):
		fileName, _ = QFileDialog.getOpenFileName(self, 'Open Script File')

		fd = open(fileName, 'r');
		self.fileCommands = []
		self.testPreview_edit.clear()
		#Read in the Contents
		with fd:
			lines = fd.readlines()

			lines = [i.strip() for i in lines]

			for i in lines:
				self.fileCommands.append(str(i))
				self.testPreview_edit.insertPlainText(str(i) + "\n")

	@Slot()
	def ClearViews(self):
		self.transmit_edit.clear()
		self.transmitHex_edit.clear()
		self.receive_edit.clear()
		self.receiveHex_edit.clear()
		return
	@Slot()
	def CombinedToggle(self):
		self.currentView = 4
		self.actionCombined_View.setEnabled(False)
		self.actionASCII_View.setEnabled(True)
		self.actionHybrid_View.setEnabled(True)
		self.actionNo_View.setEnabled(True)
		self.actionHex_View.setEnabled(True)

		self.frame_4.hide()
		self.frame_5.hide()
	@Slot()
	def HexToggle(self):
		self.currentView = 1
		self.actionCombined_View.setEnabled(True)
		self.actionHex_View.setEnabled(False)
		self.actionHybrid_View.setEnabled(True)
		self.actionNo_View.setEnabled(True)
		self.actionASCII_View.setEnabled(True)

		self.frame_4.hide()
		self.frame_5.hide()

	@Slot()
	def ASCIIToggle(self):
		self.currentView = 0
		self.actionCombined_View.setEnabled(True)
		self.actionASCII_View.setEnabled(False)
		self.actionHybrid_View.setEnabled(True)
		self.actionNo_View.setEnabled(True)
		self.actionHex_View.setEnabled(True)

		self.frame_4.hide()
		self.frame_5.hide()

	@Slot()
	def HybridToggle(self):
		self.currentView = 2
		self.actionCombined_View.setEnabled(True)
		self.actionASCII_View.setEnabled(True)
		self.actionHex_View.setEnabled(True)
		self.actionNo_View.setEnabled(True)
		self.actionHybrid_View.setEnabled(False)

		self.frame_4.show()
		self.frame_5.show()

	def NoDisplayToggle(self):
		self.currentView = 3
		self.actionCombined_View.setEnabled(True)
		self.actionNo_View.setEnabled(False)
		self.actionASCII_View.setEnabled(True)
		self.actionHybrid_View.setEnabled(True)
		self.actionHex_View.setEnabled(True)

		self.frame_4.hide()
		self.frame_5.hide()

	@Slot(bytearray, str, int)
	def RxAddText(self, recv_bytes, recv_text, length):
		hexStr = ''

		if self.currentView != 4:
			self.transmit_edit.setTextColor(QColor(255, 255, 255)) 

		if self.currentView == 4:
			self.transmit_edit.setTextColor(QColor(255, 0, 0))
			self.transmit_edit.insertPlainText(recv_text)

		elif self.currentView == 2:
			for i in range(0, length):
				hexStr += '0x%02X ' % recv_bytes[i]

			if (self.protocol_combo.currentText() == "Smithcomm Mini Host") or (self.protocol_combo.currentText() == "Smithcomm Term Host"):
				hexStr += "\n"
			else:
				if self.foundReturn:
					if recv_bytes[i] == 0x0A:
						hexStr += '\n'
					else:
						self.foundReturn = False
				if recv_bytes[i] == 0x0D:
					self.foundReturn = True

			self.receiveHex_edit.insertPlainText(hexStr)
			self.receive_edit.insertPlainText(recv_text)
		
		elif self.currentView == 1:
			for i in range(0, length):
				hexStr += '0x%02X ' % recv_bytes[i]

			if (self.protocol_combo.currentText() == "Smithcomm Mini Host") or (self.protocol_combo.currentText() == "Smithcomm Term Host"):
				hexStr += "\n"

			self.receive_edit.insertPlainText(hexStr)
		elif self.currentView == 0:
			self.receive_edit.insertPlainText(recv_text)

		if (self.testThread is not None) and self.testThread.running():
			self.testThread.setResponse(recv_bytes)

		if(self.engineThread is not None) and self.engineThread.running():
			self.engineThread.setResponse(recv_text[:len(recv_text) - 1])

		if self.currentView != 3:
			self.receive_edit.moveCursor(QTextCursor.End)
			self.receiveHex_edit.moveCursor(QTextCursor.End)



	@Slot(bytearray, str, int)
	def TxAddText(self, transmit_bytes, transmit_text, length):
		hexStr = ''

		if self.currentView == 4:
			self.transmit_edit.setTextColor(QColor(0, 255, 0)) 
		else:
			self.transmit_edit.setTextColor(QColor(255, 255, 255)) 

		if self.currentView == 2:
			for i in range(0, length):
				hexStr += '0x%02X ' % transmit_bytes[i]

			if (self.protocol_combo.currentText() == "Smithcomm Mini Host") or (self.protocol_combo.currentText() == "Smithcomm Term Host"):
				hexStr += "\n"
			else:
				if self.foundTxReturn:
					if transmit_bytes[i] == 0x0A:
						hexStr += '\n'
					else:
						self.foundTxReturn = False
				if transmit_bytes[i] == 0x0D:
					self.foundTxReturn = True

			self.transmitHex_edit.insertPlainText(hexStr)
			self.transmit_edit.insertPlainText(transmit_text)
		
		elif self.currentView == 1:
			for i in range(0, length):
				hexStr += '0x%02X ' % transmit_bytes[i]

			if (self.protocol_combo.currentText() == "Smithcomm Mini Host") or (self.protocol_combo.currentText() == "Smithcomm Term Host"):
				hexStr += "\n"

			self.transmit_edit.insertPlainText(hexStr)
		elif self.currentView == 0 or self.currentView == 4:
			self.transmit_edit.insertPlainText(transmit_text)
		if self.currentView != 3:
			self.transmit_edit.moveCursor(QTextCursor.End)
			self.transmitHex_edit.moveCursor(QTextCursor.End)

	@Slot()
	def TypeToggle(self):

		self.protocol_combo.clear()

		if self.serial_radio.isChecked():
			self.protocol_combo.addItems(PROTOCOLS_SERIAL)
			self.frame.show()
			self.frame_2.hide()

			result = []
			for port in ports:
				try:
					s = serial.Serial(port)
					s.close()
					result.append(port)
				except (OSError, serial.SerialException):
					pass

			self.com_combo.clear()
			self.com_combo.addItems(result)
		else:
			self.protocol_combo.addItems(PROTOCOLS_TCP)
			self.frame_2.show()
			self.frame.hide()

	@Slot()
	def Connect(self):
		if self.serial_radio.isChecked():
			try:
				stop = serial.STOPBITS_ONE
				if self.stop_combo is "2":
					stop = serial.STOPBITS_TWO

				par = serial.PARITY_NONE
				if self.parity_combo is "Even":
					par = serial.PARITY_EVEN
				elif self.parity_combo is "Odd":
					par = serial.PARITY_ODD
				
				self.currentSerial = serial.Serial(port=self.com_combo.currentText(), baudrate=int(self.baud_combo.currentText()), 
							bytesize = int(self.length_combo.currentText()), parity=par, stopbits=stop)
				self.currentSerial.reset_output_buffer()
				self.serThread = SerialThread(args=(self.currentSerial,self.protocol_combo))
				self.serThread.updateText.connect(self.RxAddText)
				self.serThread.start()
				print "Opened"
			except(OSError, serial.SerialException):
				#Error Popup
				print "Error"
				return

			print "Connected to" + self.com_combo.currentText()

		if self.tcp_radio.isChecked():
			text = str(self.ip_line.text())
			if not text:
				return

			if ":" in text:
				pos = text.find(':')
				if pos > len(text):
					return
	
				port = int(text[pos + 1:])
			else:
				return

			self.currentTCP = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			ip_addr = socket.gethostbyname(text[:pos])
			print "Connecting to " + ip_addr + " On Port " + str(port)
			
			try:
				self.currentTCP.settimeout(1)
				self.currentTCP.connect((ip_addr, port))
			except socket.error as msg:
				self.currentTCP.close()
				return
			self.tcpThread = TCPThread(args=(self.currentTCP,self.protocol_combo, self.currentSerial,self.protocol_combo))
			self.tcpThread.updateText.connect(self.RxAddText)
			self.tcpThread.start()

			if self.protocol_combo.currentText() == "AICB":
				self.engineThread = AICB.AICBEngine((self.currentSerial, self.protocol_combo.currentText(), self.serial_radio, self.currentTCP))
				self.engineThread.updateText.connect(self.TxAddText)
				self.engineThread.start()

		self.connect_button.setText("Disconnect")

		self.connect_button.pressed.disconnect()
		self.connect_button.pressed.connect(self.Disconnect)

		self.com_combo.setEnabled(0)
		self.send_button.setEnabled(1)

		#Fill the Test Combo Box
		self.test_combo.clear()
		self.test_combo.addItems(commands.smith_test.keys())

	@Slot()
	def Disconnect(self):
		if self.serial_radio.isChecked():

			self.serThread.stop()
			while self.serThread.running():
				time.sleep(0.5)

			try:
				self.currentSerial.close()
				self.currentSerial = None
			except(OSError, serial.SerialException):
				#Error Popup
				print "Error"
				return

			print "Disconnected from" + self.com_combo.currentText()

		if self.tcp_radio.isChecked():
			self.tcpThread.stop()
			while self.tcpThread.running():
				time.sleep(0.5)

			try:
				self.currentTCP.close()
				self.currentTCP = None
			except(OSError):
				#Error Popup
				print "Error"
				return
	
			print "Socket Closed"

		if self.engineThread is not None and self.engineThread.running():
			self.engineThread.stop()
			while self.engineThread.running():
				time.sleep(0.5)

		self.connect_button.setText("Connect")
		self.connect_button.pressed.disconnect()
		self.connect_button.pressed.connect(self.Connect)
		self.com_combo.setEnabled(1)
		self.send_button.setEnabled(0)

	@Slot()
	def SendCommand(self):
		if (not self.currentSerial and self.serial_radio.isChecked()) or (not self.currentTCP and self.tcp_radio.isChecked()):
			print "Not Connected"
			return
		if not self.command_line.text():
			return

		command = bytearray()

		if self.serial_radio.isChecked():
			command = commands.formatCommand(self.protocol_combo.currentText(), self.command_line.text())
			self.currentSerial.reset_output_buffer()
			self.currentSerial.write(command)
		else:
			command = commands.formatCommand(self.protocol_combo.currentText(), self.command_line.text())
			self.currentTCP.sendall(command)

		self.TxAddText(command, self.command_line.text() + "\n", len(command))

		self.command_line.clear()

	@Slot()
	def StartTest(self):
		if ((self.currentSerial is None) and self.serial_radio.isChecked()) or ((self.currentTCP is None) and self.tcp_radio.isChecked()):
			print "Not Connected"
 		else:
			#Check to See if We Are Running a Macro
			if self.macro_state:
				#Start the Marco Engine
				self.engineThread = Macro.MacroEngine((self.serial_radio.isChecked(), self.currentSerial, self.currentTCP, self.fileCommands, self.protocol_combo.currentText()))
				self.engineThread.updateText.connect(self.TxAddText)
				self.engineThread.testStopTest.connect(self.StopTest)
				self.engineThread.start()

				self.start_button.setEnabled(False)
				self.stop_button.setEnabled(True)
				return

			if commands.smith_test[self.test_combo.currentText()] is not None:

				test = str(self.test_combo.currentText())
				print "Starting " + test

				#Start the Test Thread
				self.test_combo.setEnabled(False)
				self.start_button.setEnabled(False)
				self.connect_button.setEnabled(False)
				self.stop_button.setEnabled(True)

				self.testThread = commands.smith_test[self.test_combo.currentText()]((self.currentSerial, self.protocol_combo.currentText(), self.serial_radio, self.currentTCP))
				self.testThread.updateText.connect(self.TxAddText)
				self.testThread.testStopTest.connect(self.StopTest)
				self.testThread.start()
			else:
				print "Test Not Supported"
	@Slot()
	def StopTest(self):
		print "Stopping Test"
		if ((self.currentSerial is None) and self.serial_radio.isChecked()) or ((self.currentTCP is None) and self.tcp_radio.isChecked()):
			print "Not Connected"
			return

		if not self.macro_state:
			if self.testThread is not None and self.testThread.running():
				self.testThread.stop()

				while self.testThread.running():
						time.sleep(0.5)
		else:
			if self.engineThread is not None and self.engineThread.running():
				self.engineThread.stop()

			while self.engineThread.running():
				time.sleep(0.5)

			if not self.macro_state:
				self.test_combo.setEnabled(True)

			self.start_button.setEnabled(True)
			self.connect_button.setEnabled(True)
			self.stop_button.setEnabled(False)
			self.test_combo.setEnabled(True)

	@Slot()
	def TivaUnlock(self):

		if self.currentSerial is None:
			return

		self.currentSerial.reset_output_buffer()
		self.currentSerial.write("\x1B")

		time.sleep(0.01)
		for i in TIVA_UNLOCK_CODE:
			self.currentSerial.write(i)
			time.sleep(0.01)
		self.currentSerial.write("\x1B")

	def closeEvent(self, event):
		#Thread Closing and Connect Closing
		if self.serThread is not None:
			if self.serThread.running():
				self.serThread.stop()
				while self.serThread.running():
					time.sleep(0.5)

			if self.currentSerial is not None:
				try:
					self.currentSerial.close()
					self.currentSerial = None
				except(OSError, serial.SerialException):
					#Error Popup
					print "Error"
					return

		if self.tcpThread is not None:
			if self.tcpThread.running():
				self.tcpThread.stop()
				while self.tcpThread.running():
					time.sleep(0.5)
			if self.currentTCP is not None:
				try:
					self.currentTCP.close()
					self.currentTCP = None
				except(OSError):
					#Error Popup
					print "Error"
					return

		if self.testThread is not None and self.testThread.running():
			self.testThread.stop()
		
		while self.testThread.running():
			time.sleep(0.5)

		if self.engineThread is not None and self.engineThread.running():
			self.engineThread.stop()
			while self.engineThread.running():
				time.sleep(0.5)

		exit(0)


	def __init__(self):
		super(MainWindow, self).__init__()
		self.setupUi(self)

		self.serThread = None
		self.tcpThread = None
		self.currentTCP = None
		self.currentSerial = None
		self.testThread = None
		self.engineThread = None
		self.macro_state = False
		self.actionASCII_View.setEnabled(False)

		self.currentView = 0
		self.fileCommands = []

		if self.serial_radio.isChecked():
			self.protocol_combo.addItems(PROTOCOLS_SERIAL)
			self.frame.show()
			self.frame_2.hide()
		else:
			self.protocol_combo.addItems(PROTOCOLS_TCP)
			self.frame_2.show()
			self.frame.hide()

		self.frame_4.hide()
		self.frame_5.hide()

		self.send_button.setEnabled(0)

		#Widget Initialization
		self.baud_combo.addItems(BAUD)
		self.baud_combo.setCurrentIndex(self.baud_combo.findText("9600"))
		self.stop_combo.addItem("None")
		self.stop_combo.addItem("Even")
		self.stop_combo.addItem("Odd")

		self.parity_combo.addItem("1")
		self.parity_combo.addItem("2")

		self.length_combo.addItem("7")
		self.length_combo.addItem("8")
		self.length_combo.setCurrentIndex(1)
		
		result = []
		for port in ports:
			try:
			    s = serial.Serial(port)
			    s.close()
			    result.append(port)
			except (OSError, serial.SerialException):
			    pass

		self.com_combo.addItems(result)

		#Menu Buttons
		self.actionOpen.setShortcut('Ctrl+O')
		self.actionSave.setShortcut('Ctrl+S')
		self.actionHex_View.setShortcut('Ctrl+H')
		self.actionASCII_View.setShortcut('Ctrl+A')

		self.actionOpen.triggered.connect(self.OpenFile)
		#self.actionSave.triggered.connect('Ctrl+S')
		self.actionHex_View.triggered.connect(self.HexToggle)
		self.actionASCII_View.triggered.connect(self.ASCIIToggle)
		self.actionHybrid_View.triggered.connect(self.HybridToggle)
		self.actionNo_View.triggered.connect(self.NoDisplayToggle)
		self.actionCombined_View.triggered.connect(self.CombinedToggle)
		self.actionClear_All.triggered.connect(self.ClearViews)

		#Signals
		self.serial_radio.clicked.connect(self.TypeToggle)
		self.tcp_radio.clicked.connect(self.TypeToggle)
		self.connect_button.pressed.connect(self.Connect)
		self.send_button.pressed.connect(self.SendCommand)
		self.start_button.pressed.connect(self.StartTest)
		self.stop_button.pressed.connect(self.StopTest)
		self.macro_checkbox.stateChanged.connect(self.MacroChange)

		self.unlock_tiva_button.pressed.connect(self.TivaUnlock)
		#self.addTab_button.pressed.connect(self.AddTab)
		#self.removeTab_button.pressed.connect(self.RemoveTab)

		#Keyboard Shortcuts
		self.command_line.returnPressed.connect(self.SendCommand)
		
		self.show()

if __name__ == '__main__':
	app = QApplication(sys.argv)
	mainWin = MainWindow()
	ret = app.exec_()
	sys.exit( ret )
