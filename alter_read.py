import serial
import time
import re
port = 'COM7'
baudrate = 9600
detik = 0
try:
    ser = serial.Serial(port, baudrate, timeout=1)
    time.sleep(2)
    print("Membaca data warna dari Arduino...\n")
    with open("percobaan1.txt", "a") as file:
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()
                match = re.match(
                    r"Color Temp: (\d+) K - Lux: (\d+) - R: (\d+) G: (\d+) B: (\d+) C: (\d+)", line
                )
                if match:
                    color_temp = int(match.group(1))
                    lux = int(match.group(2))
                    r = int(match.group(3))
                    g = int(match.group(4))
                    b = int(match.group(5))
                    c = int(match.group(6))
                    data_str = f"detik ke: {detik},Color Temp: {color_temp} K, Lux: {lux}, R: {r}, G: {g}, B: {b}, C: {c}"
                    print(data_str)
                    file.write(data_str + "\n")
                    file.flush()
                else:
                    print("Data tidak sesuai format:", line)
                detik += 1
except serial.SerialException as e:
    print(f"Gagal membuka port serial: {e}")
except KeyboardInterrupt:
    print("\nProgram dihentikan oleh pengguna.")
finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Port serial ditutup.")
