import serial
import time
PORT = "COM7"
BAUDRATE = 9600
OUTPUT_FILE = "./STOPING_DATA/07072025_5th_run.txt"
def main():
    try:
        ser = serial.Serial(PORT, BAUDRATE, timeout=1)
        time.sleep(2)
        print(f"[INFO] Membaca dari {PORT} @ {BAUDRATE} baud...")
        start_time = time.time()
        with open(OUTPUT_FILE, "w") as file:
            while True:
                if ser.in_waiting:
                    line = ser.readline().decode("utf-8", errors="ignore").strip()
                    timestamp = int(time.time() - start_time)  # detik ke-n
                    output_line = f"[detik ke-{timestamp}] {line}"
                    print(output_line)
                    file.write(output_line + "\n")
                    file.flush()
    except KeyboardInterrupt:
        print("\n[EXIT] Dihentikan oleh pengguna.")
    except Exception as e:
        print(f"[ERROR] {e}")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
        print("[INFO] Serial port ditutup.")
if __name__ == "__main__":
    main()
