# CYLUX 3.0 - Arduino Color Detection & Motor Control System
<p align="center">
   <img src="https://www.aiche.org/sites/default/files/images/page/embeded/chem-e-car_logo_2.png" width="200"><br>
   <img src="https://github.com/athallahrafi/CYLUX3.0/blob/main/IMG-20250612-WA0037.jpg" width="200">
</p>

## 🎯 Deskripsi Proyek

**CYLUX 3.0** adalah sistem Chem E-Car yang menggunakan sensor warna **TCS34725** dan Peristaltic Pump sebagai pengatur laju reaksi Iodine Clock, mengendalikan LED indikator, serta menggerakkan aktuator berdasarkan input tombol dan berhenti berdasarkan reaksi kimia.

Proyek ini dikembangkan untuk keperluan partisipasi kompetisi pada Chem-E Car Beijing 2025.

---

## 🛠️ Fitur Utama

- 🎨 Deteksi warna menggunakan sensor TCS34725.
- 💡 Indikasi LED RGB (Merah, Kuning, Hijau) berdasarkan status sistem.
- ⚙️ Kendali dua aktuator motor (Motor A & Peristaltic Pump).
- 🧠 Trigger berbasis tombol dengan Stoping Mechanism berdasarkan warna reaksi.
- 🔍 Output data warna (RGB, lux, temperatur warna) via Serial Monitor.
- 🧪 Siap untuk dikembangkan lebih lanjut (misal: klasifikasi warna, machine learning ringan).

---

## 🧰 Komponen Hardware

| Komponen               | Jumlah |
|------------------------|--------|
| Arduino Uno/Nano       | 1      |
| Sensor TCS34725        | 1      |
| Motor Driver (L298N)   | 1      |
| Tombol Push Button     | 1      |
| LED RGB (3 kanal)      | 3      |
| Power Supply +12V      | 1      |

---

## 🧑‍💻 Instalasi

1. Clone atau download repository ini:

   ```bash
   git clone https://github.com/athallahrafi/cylux3.0.git
   cd CYLUX3.0
