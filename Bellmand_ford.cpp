#include <climits>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Menyimpan asal, tujuan, dan bobot edge.
 */
struct Edge {
  int asal;         ///< Simpul asal dari sisi.
  int tujuan;       ///< Simpul tujuan dari sisi.
  long long bobot;  ///< Nilai numerik (bobot) sisi.
};

/**
 * @brief Menampilkan jarak terpendek dari simpul awal ke setiap simpul yang ada dalam graph berarah berbobot.
 * 
 * @param[in] jumlahSimpul Jumlah simpul yang berada pada graph berarah berbobot.
 * @param[in] awal Simpul awal yang akan dicari jarak terpendeknya ke setiap simpul ada.
 * @param[in] daftarSisi Daftar koneksi antar simpul yang memiliki arah tertentu dan nilai numerik (bobot).
 * 
 * @post Menampilkan jarak terpendek dari simpul awal ke setiap simpul di graph.
 */
void bellmanFordOptimized(int jumlahSimpul, int awal, const vector<Edge> &daftarSisi) {
  // Menggunakan LLONG_MAX agar aman untuk bobot yang besar
  vector<long long> jarak(jumlahSimpul, LLONG_MAX);
  jarak[awal] = 0;

  bool adaPerubahan;

  // Relaksasi dengan optimasi Early Termination.
  for (int i = 1; i <= jumlahSimpul - 1; i++) {
    adaPerubahan = false;

    for (const auto &sisi : daftarSisi) {
      if (jarak[sisi.asal] != LLONG_MAX &&
          jarak[sisi.asal] + sisi.bobot < jarak[sisi.tujuan]) {
        jarak[sisi.tujuan] = jarak[sisi.asal] + sisi.bobot;
        adaPerubahan = true; // Tandai bahwa ada jarak yang diperbarui.
      }
    }

    /* 
    OPTIMASI UTAMA: Jika tidak ada perubahan pada iterasi ini, jarak terpendek sudah final. 
    Langsung hentikan loop!
    */
    if (!adaPerubahan) {
      break;
    }
  }

  // Cek siklus negatif HANYA jika loop sebelumnya berjalan penuh (jumlahSimpul - 1 kali)
  if (adaPerubahan) {
    for (const auto &sisi : daftarSisi) {
      if (jarak[sisi.asal] != LLONG_MAX &&
          jarak[sisi.asal] + sisi.bobot < jarak[sisi.tujuan]) {
        cout << "Graf mengandung siklus berbobot negatif!" << endl;
        return;
      }
    }
  }

  // Cetak hasil
  cout << "Jarak terpendek dari simpul " << awal << ":\n";
  for (int i = 0; i < jumlahSimpul; i++) {
    cout << "Ke simpul " << i << " : ";
    if (jarak[i] == LLONG_MAX)
      cout << "Tidak terjangkau" << endl;
    else
      cout << jarak[i] << endl;
  }
}

/**
 * @brief Titik awal program mencari jarak terpendek dari simpul awal ke setiap simpul.
 * 
 * Menginisialisasi data awal dan memanggil function untuk menampilkan hasil jarak terpendek setiap simpul.
 * 
 * @return 0 Jika program berjalan dan keluar dengan normal.
 */
int main() {
  int jumlahSimpul = 5;
  vector<Edge> daftarSisi = {{0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2},
                       {1, 4, 2},  {3, 2, 5}, {3, 1, 1}, {4, 3, -3}};

  int simpulAwal = 0;
  bellmanFordOptimized(jumlahSimpul, simpulAwal, daftarSisi);

  return 0;
}
