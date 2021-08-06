/*                                                                       
 *                                                                       
 * pal16l8.c V1.0 (c) Dieter Mueller 08/2004                             
 *                                                                       
 * example: using a 64kB EPROM as programmable logic device.             
 * 27512, gives 16 Input_Pins and 8 Output_Pins.                         
 *                                                                       
 * Note: unlike with PALs/GALS, the number/complexity of                 
 * product_terms/equations is only limited by the Pin count              
 * of the EPROM... and the abilities of your compiler.                   
 *                                                                       
 * Not much memory used, generating 1MB files for 27080                  
 * should be possible under DOS.                                         
 *                                                                       
 */                                                                      
                                                                         
#include <stdio.h>
#include <stdlib.h>
                                                                         
int main(void);                                                          
char do_rom(long addr);                                                  
                                                                         
int main(void)                                                           
{                                                                        
	FILE *outstream;                                                       
																		   
	long i;                                                                
																		   
	outstream=fopen("pal16l8.bin","wb");                                   
	if(outstream==NULL)                                                    
	{                                                                      
		printf("\nFile open error.\n");                                      
		return(-1);                                                          
	}                                                                      
																		   
	for(i=0; i<0x10000; i++) //try all possible input patterns, 64 kBytes   
	{                                                                      
		fputc(do_rom(i),outstream); //write one EPROM Byte                   
	}                                                                      
																		   
	fclose(outstream);                                                     
	return(0);                                                             
}                                                                        
                                                                         
char do_rom(long addr) //do one Byte                                     
{                                                                        
	char out;                                                              
	char a,b,c;                                                            
	char q0,q1,q2;                                                         
																		 
	//default = Zero.                                                       
	a=0; b=0; c=0; q0=0; q1=0; q2=0;                                       
																		 
	//scan input_pins. //WARNING: casting HAS to be, avoiding funny results.
	if((long)addr & 0x01) a=-1;                                            
	if((long)addr & 0x02) b=-1;                                            
	if((long)addr & 0x04) c=-1;                                            
																		 
	//equations. //WARNING: thou shalt not use ! to negate.                 
	q0=a|b;                                                                
	q1=a&b;                                                                
	q2=(~a&b)^c; //((NOT A) AND B) XOR C //last stage of a full adder      
																		 
	//now to throw all the results together.                                
	out=0; //default = Zero.                                               
	if(q0) out|=0x01;                                                      
	if(q1) out|=0x02;                                                      
	if(q2) out|=0x04;                                                      
																		 
	//done.                                                                 
	return(out);                                                           
} 
