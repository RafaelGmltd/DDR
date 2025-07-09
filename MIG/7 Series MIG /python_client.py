import serial
# import time

ser = serial.Serial("/dev/ttyUSB1", 115200, timeout = 0.1)

# === 1. Sending data for writing (the string "Hello World")===

# data_to_send = b"Hello World"
# packet = bytes([0x01, len(data_to_send)]) + data_to_send
# print(f"[WRITE] Sending: {packet.hex()} ({data_to_send.decode()})")
# ser.write(packet)

text = input("Enter text to write into DDR: ")
data = text.encode()
packet = bytes([0x01, len(data)]) + data
ser.write(packet)


# time.sleep(0.1)

# === 2. Sending the read command ===

ser.write(bytes([0x02]))
print("[READ] Requesting data back...")

response = ser.read(256)
print(f"[READ] Received {len(response)} bytes: {response[:len(data)].decode()}")

ser.close()