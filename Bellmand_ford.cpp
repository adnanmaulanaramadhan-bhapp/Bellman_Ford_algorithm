#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int asal, tujuan;
  long long bobot; // Menggunakan long long untuk mencegah overflow
};

void bellmanFordOptimized(int jumlahSimpul, int awal,
                          const vector<Edge> &daftarSisi) {
  // Menggunakan LLONG_MAX agar aman untuk bobot yang besar
  vector<long long> jarak(jumlahSimpul, LLONG_MAX);
  jarak[awal] = 0;

  bool adaPerubahan;

  // 1. Relaksasi dengan optimasi Early Termination
  for (int i = 1; i <= jumlahSimpul - 1; i++) {
    adaPerubahan = false;

    for (const auto &sisi : daftarSisi) {
      if (jarak[sisi.asal] != LLONG_MAX &&
          jarak[sisi.asal] + sisi.bobot < jarak[sisi.tujuan]) {
        jarak[sisi.tujuan] = jarak[sisi.asal] + sisi.bobot;
        adaPerubahan = true; // Tandai bahwa ada jarak yang diperbarui
      }
    }

    // OPTIMASI UTAMA: Jika tidak ada perubahan pada iterasi ini,
    // jarak terpendek sudah final. Langsung hentikan loop!
    if (!adaPerubahan) {
      break;
    }
  }

  // 2. Cek siklus negatif HANYA jika loop sebelumnya berjalan penuh (V - 1
  // kali)
  if (adaPerubahan) {
    for (const auto &sisi : daftarSisi) {
      if (jarak[sisi.asal] != LLONG_MAX &&
          jarak[sisi.asal] + sisi.bobot < jarak[sisi.tujuan]) {
        cout << "Graf mengandung siklus berbobot negatif!" << endl;
        return;
      }
    }
  }

  // 3. Cetak hasil
  cout << "Jarak terpendek dari simpul " << awal << ":\n";
  for (int i = 0; i < jumlahSimpul; i++) {
    cout << "Ke simpul " << i << " : ";
    if (jarak[i] == LLONG_MAX)
      cout << "Tidak terjangkau" << endl;
    else
      cout << jarak[i] << endl;
  }
}

int main() {
  int V = 5;
  vector<Edge> sisi = {{0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2},
                       {1, 4, 2},  {3, 2, 5}, {3, 1, 1}, {4, 3, -3}};

  int simpulAwal = 0;
  bellmanFordOptimized(V, simpulAwal, sisi);

  return 0;
}
