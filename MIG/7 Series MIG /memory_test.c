#include "xparameters.h"    // Hardware platform parameters (addresses, device IDs)
#include "xil_types.h"      // Data type definitions (u8, u32, etc.)
#include "xil_printf.h"     // UART output (printf-like)
#include "xuartlite.h"      // UART Lite driver
#include "xil_io.h"         // Memory read/write functions
#include "platform.h"       // Platform init/cleanup


#define UART_DEVICE_ID      XPAR_UARTLITE_0_DEVICE_ID
#define DDR_BASE_ADDR       0x80000000                      // Base address of DDR memory
#define MAX_DATA_LEN        256                             // Max buffer length

XUartLite Uart;                 // UART instance
u8 buffer[MAX_DATA_LEN];        // Data buffer
static u8 write_len = 0;        // Number of bytes written to DDR

int main() {
    init_platform();
    XUartLite_Initialize(&Uart, UART_DEVICE_ID);

    xil_printf("--UART DDR Echo Handler--\n\r");

    while (1) {
        u8 cmd = 0;

        // Wait for a 1-byte command over UART
        while (XUartLite_Recv(&Uart, &cmd, 1) == 0);

        if (cmd == 0x01) {
            u8 len = 0;
            while (XUartLite_Recv(&Uart, &len, 1) == 0);
            if (len > MAX_DATA_LEN) len = MAX_DATA_LEN;

            u32 received = 0;
            while (received < len) {
                received += XUartLite_Recv(&Uart, buffer + received, len - received);
            }

            // Write to DDR
            for (int i = 0; i < len; i++) {
                Xil_Out8(DDR_BASE_ADDR + i, buffer[i]);
            }

            write_len = len; // Save length

        } else if (cmd == 0x02) {
            // Clear buffer before reading
            for (int i = 0; i < MAX_DATA_LEN; i++) {
                buffer[i] = 0x00;
            }

            // Read from DDR
            for (int i = 0; i < write_len; i++) {
                buffer[i] = Xil_In8(DDR_BASE_ADDR + i);
            }

            XUartLite_Send(&Uart, buffer, write_len);
        }
    }

    cleanup_platform();
    return 0;
}
