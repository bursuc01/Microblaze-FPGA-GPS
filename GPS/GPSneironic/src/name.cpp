#include "xparameters.h"
#include "xstatus.h"
#include "xuartlite.h"
#include "xil_printf.h"
#include "String.h"
#include "stdio.h"

/************************** Constant Definitions *****************************/
#define UARTLITE_DEVICE_ID_0 XPAR_UARTLITE_0_DEVICE_ID
#define UARTLITE_DEVICE_ID_1 XPAR_UARTLITE_1_DEVICE_ID
#define TEST_BUFFER_SIZE 16
int UartLitePolledExample(u16 DeviceId);
char lat[100];
char lng[100];


/************************** Variable Definitions *****************************/
XUartLite UartLite_0; /* Instance of the UartLite Device */
XUartLite UartLite_1; /* Instance of the UartLite Device */
/*
* The following buffers are used in this example to send and receive data
* with the UartLite.
*/
u8 SendBuffer[TEST_BUFFER_SIZE]; /* Buffer for Transmitting Data */
u8 RecvBuffer[TEST_BUFFER_SIZE]; /* Buffer for Receiving Data */
int main(void) {
int Status;


void getLocation(u8 Recv[TEST_BUFFER_SIZE]);
/*
* Run the UartLite polled example, specify the Device ID that is
* generated in xparameters.h
*/
Status = XUartLite_Initialize(&UartLite_0, UARTLITE_DEVICE_ID_0);
if (Status != XST_SUCCESS) {
return XST_FAILURE;
}
if (Status != XST_SUCCESS) {
xil_printf("Uartlite polled Example Failed\r\n");
return XST_FAILURE;
}
Status = XUartLite_Initialize(&UartLite_1, UARTLITE_DEVICE_ID_1);
if (Status != XST_SUCCESS) {
return XST_FAILURE;
}
if (Status != XST_SUCCESS) {
xil_printf("Uartlite polled Example Failed\r\n");
return XST_FAILURE;
}
xil_printf("Successfully ran Uartlite polled Example\r\n");
//XUartLite_Send(&UartLite_0, SendBuffer, TEST_BUFFER_SIZE);
int temp = 80000;
int simplecounter = 0;
char links[] = "DIGILENT DIGILENT\n\0";
char linksx[] = "ARTY ARTY ARTY ARTY\n\0";
while (1) {
if (1) {
//xil_printf("Cha Cha Cha.... %d\r\n", simplecounter++);
temp = 80000;
XUartLite_Recv(&UartLite_1,RecvBuffer,1);
xil_printf("%s", RecvBuffer);
//getLocation(RecvBuffer);
//xil_printf("Latititude: %s\n", lat);
//xil_printf("Longitude: %s\n", lng);
}
}
return XST_SUCCESS;
}

bool split(u8 Recv[TEST_BUFFER_SIZE]){
	char str[100];
	sprintf(str,"%s",Recv);
	char *ptr; // declare a ptr pointer
	    ptr = strtok(str, " , "); // use strtok() function to separate string using comma (,) delimiter.
	    //cout << " \n Split string using strtok() function: " << endl;
	    // use while loop to check ptr is not null
	    while (ptr != NULL)
	    {
	        //cout << ptr  << endl; // print the string token
	        if (strcmp(ptr,"$GPGGA"))
	        		return true;
	        ptr = strtok (NULL, " , ");
	    }
	return false;
}

void getLocation(u8 Recv[TEST_BUFFER_SIZE]){
	int i=0;
	if(split(Recv)){
		char str[100];
			sprintf(str,"%s",Recv);
			char *ptr; // declare a ptr pointer
			    ptr = strtok(str, " , "); // use strtok() function to separate string using comma (,) delimiter.
			    //cout << " \n Split string using strtok() function: " << endl;
			    // use while loop to check ptr is not null
			    while (i < 4)
			    {
			    	if(i = 1)
			    		strcpy(lat,ptr);
			    	if(i = 3)
			    		strcpy(lng,ptr);
			    	ptr = strtok (NULL, " , ");
			    	i++;
			    }
	}
}

