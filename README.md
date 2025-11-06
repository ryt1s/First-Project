# Studentų Duomenų Valdymo Tyrimas ir Spartos Optimizacija  
Šis projektas analizuoja studentų duomenų apdorojimo (nuskaitymo, rūšiavimo ir skirstymo) spartą, lyginant **std::vector** ir **std::list** konteinerius. Ypatingas dėmesys skirtas duomenų skirstymo **T_split** strategijų palyginimui bei I/O operacijų optimizacijai.

## 1. Testavimo sistemos parametrai

| Parametras | Reikšmė |
|------------|---------|
| Procesorius (CPU) | AMD Ryzen 7 8845HS w/ Radeon 780M Graphics 3.80 GHz |
| Operatyvioji atmintis (RAM) | 16 GB DDR4 |
| Duomenų saugykla (SSD) | 954 GB NVMe SSD |
| Operacinė sistema | Windows 11 |

## 2. Split strategijų palyginimas  

### 2.1. Kodo optimacijos santrauka  

* **Strategija 1 – Kopijavimas į du naujus konteinerius:** lėčiausia, daug atminties reikalaujanti operacija.  
* **Strategija 2 – Kopijavimas + Trynimas/Perkėlimas:** efektyvesnė atminties atžvilgiu, tačiau `vector` konteineryje dideliam kiekiui duomenų trynimai sulėtina operaciją.  
* **Strategija 3 – Efektyviausias (Partition / Splice + Move):** `vector` naudoja `partition` + `move`, `list` naudoja `splice`, greičiausia operacija abiem konteinerių tipams.  
* **I/O optimizacija:** `T_write` greitis pagerintas naudojant buferizuotą įrašymą.

### 2.2. Strategija 1: Kopijavimas į du naujus konteinerius

| Konteineris | Dydis (N) | T_read (s) | T_sort (s) | T_split (s) | T_write (s) | T_total (s) |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Vector** | 1 000 | 0.00426 | 0.00209 | 0.00068 | 0.06206 | 0.06908 |
| **Vector** | 10 000 | 0.03108 | 0.02259 | 0.00769 | 0.01211 | 0.07349 |
| **Vector** | 100 000 | 0.25818 | 0.30211 | 0.06270 | 0.09579 | 0.71878 |
| **Vector** | 1 000 000 | 2.71694 | 4.02959 | 0.63888 | 0.90804 | 8.29345 |
| **Vector** | 10 000 000 | 27.65686 | 48.48721 | 6.51016 | 8.68069 | 91.33493 |
| **List** | 1 000 | 0.00288 | 0.00034 | 0.00074 | 0.00268 | 0.00663 |
| **List** | 10 000 | 0.02849 | 0.00439 | 0.00793 | 0.01251 | 0.05332 |
| **List** | 100 000 | 0.25659 | 0.05682 | 0.11861 | 0.08181 | 0.51382 |
| **List** | 1 000 000 | 2.49096 | 1.00429 | 1.52834 | 1.02963 | 6.05321 |
| **List** | 10 000 000 | 24.86786 | 16.79915 | 14.62552 | 8.95766 | 65.25019 |

### 2.3. Strategija 2: Kopijavimas + Trynimas / Perkėlimas

| Konteineris | Dydis (N) | T_read (s) | T_sort (s) | T_split (s) | T_write (s) | T_total (s) |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Vector** | 1 000 | 0.00292 | 0.00181 | 0.00047 | 0.00218 | 0.00738 |
| **Vector** | 10 000 | 0.02950 | 0.02318 | 0.00575 | 0.01168 | 0.07011 |
| **Vector** | 100 000 | 0.26064 | 0.31049 | 0.06289 | 0.09018 | 0.72420 |
| **Vector** | 1 000 000 | 2.51366 | 3.88816 | 0.51577 | 0.88671 | 7.80429 |
| **Vector** | 10 000 000 | 25.75138 | 47.59537 | 4.99176 | 8.75401 | 87.09252 |
| **List** | 1 000 | 0.00389 | 0.00036 | 0.00042 | 0.00219 | 0.00686 |
| **List** | 10 000 | 0.02945 | 0.00399 | 0.00603 | 0.01284 | 0.05231 |
| **List** | 100 000 | 0.25477 | 0.05964 | 0.07157 | 0.08752 | 0.47349 |
| **List** | 1 000 000 | 2.59597 | 0.88101 | 0.78605 | 0.88448 | 5.14752 |
| **List** | 10 000 000 | 24.77863 | 13.74636 | 8.18777 | 8.80382 | 55.51657 |

### 2.4. Strategija 3: Efektyviausias (Partition / Splice + Move)

| Konteineris | Dydis (N) | T_read (s) | T_sort (s) | T_split (s) | T_write (s) | T_total (s) |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Vector** | 1 000 | 0.00298 | 0.00182 | 0.00019 | 0.00275 | 0.00774 |
| **Vector** | 10 000 | 0.02840 | 0.02109 | 0.00128 | 0.01294 | 0.06371 |
| **Vector** | 100 000 | 0.24466 | 0.30531 | 0.01462 | 0.10187 | 0.66645 |
| **Vector** | 1 000 000 | 2.43081 | 3.90824 | 0.15274 | 0.89834 | 7.39013 |
| **Vector** | 10 000 000 | 26.17001 | 47.83257 | 1.44954 | 8.55936 | 84.01148 |
| **List** | 1 000 | 0.00288 | 0.00033 | 0.00056 | 0.00239 | 0.00615 |
| **List** | 10 000 | 0.02703 | 0.00392 | 0.01166 | 0.01557 | 0.05818 |
| **List** | 100 000 | 0.24459 | 0.05735 | 0.09747 | 0.08525 | 0.48504 |
| **List** | 1 000 000 | 2.54623 | 0.85054 | 1.16016 | 0.89102 | 5.44795 |
| **List** | 10 000 000 | 24.70927 | 13.29820 | 12.20798 | 8.54048 | 58.75593 |

## 3. Galutinės išvados

1. **Strategijos efektyvumas (Vector):**  
   - Strategija 1 yra lėčiausia dėl dvigubo kopijavimo.  
   - Strategija 2 gerina atminties naudojimą, tačiau trynimai su `vector` dideliam kiekiui studentų lėtina veikimą.  
   - Strategija 3 – optimaliausia: `partition` + `move` žymiai sumažina T_split laiką (pvz., 10 mln. įrašų nuo 6,51 s Strategijoje 1 iki 1,45 s Strategijoje 3).  

2. **Strategijos efektyvumas (List):**  
   - List konteineris gerai tvarkosi su trynimais ir `splice` operacijomis, todėl Strategijos 2 ir 3 spartos skirtumai nėra tokie dideli kaip `vector`.   

3. **Bendros rekomendacijos:**  
   - Dideliam kiekiui studentų duomenų Strategija 3 yra geriausias pasirinkimas, nepriklausomai nuo konteinerio tipo.  
   - Vector konteineriuose būtina naudoti `partition` + `move`, o list – `splice`.

## 4. Naudojimo ir diegimo instrukcija  

### Windows su CMake  

## 🧩 Naudojimosi ir diegimo instrukcija

Atsisiųskite projektą iš GitHub:
   ```bash
   git clone https://github.com/<jusu_vartotojas>/<projektas>.git
```
Įeikite į projekto aplanką:

```bash
cd First-Project
```
Sukurkite naują aplanką build ir jį atidarykite:

```bash
mkdir build && cd build
```
Sugeneruokite projektą su CMake:

```bash
cmake ..
```
Sukompiliuokite programą:

```bash
cmake --build .
```
Paleiskite programą:

```bash
./main
```
## **4. Vizualūs rezultatai**

### Skaičiavimo pavyzdžiai naudojant *Vector* konteinerius:

![Vector Example 1](https://github.com/user-attachments/assets/c508d899-248c-404c-b5ee-10b31caf6f9f)  
![Vector Example 2](https://github.com/user-attachments/assets/fd0a6750-a4d6-42e3-9916-2063df1ef2e7)  
![Vector Example 3](https://github.com/user-attachments/assets/94cb8a08-8a32-46ec-b0da-76197416fb95)  
![Vector Example 4](https://github.com/user-attachments/assets/611e5677-2280-4252-bca2-e65c9f6ff15b)  
![Vector Example 5](https://github.com/user-attachments/assets/88fd9cb0-a819-4153-a899-f1aa3155787a)

---

### Skaičiavimo pavyzdžiai naudojant *List* konteinerius:

![List Example 1](https://github.com/user-attachments/assets/bda61b48-0e85-4484-b2be-ec6af04cfc33)  
![List Example 2](https://github.com/user-attachments/assets/75b2c498-06d3-4bb2-9476-8f2c9a5c4fb8)  
![List Example 3](https://github.com/user-attachments/assets/7f4e7f7a-ad40-4682-b964-33fc2af16ebf)  
![List Example 4](https://github.com/user-attachments/assets/52e4421b-441f-49a2-86f5-83c9702b7b01)  
![List Example 5](https://github.com/user-attachments/assets/6488d074-f4eb-4623-9e2c-82edc3bab234)

---

## 5. Apibendrinimas

Atliktas eksperimentas parodė, kad:

- **Vector konteineris**  
  - Efektyvus mažesniems ir vidutinio dydžio duomenų kiekiams.  
  - Dideliuose duomenų rinkiniuose (10 mln. įrašų) veikimo sparta ženkliai mažėja dėl dažnų trynimų ir kopijavimo operacijų.  
  - Strategija 3 (Partition + Move) žymiai sumažina T_split laiką, todėl rekomenduojama dideliems failams.

- **List konteineris**  
  - Nors mažesniuose testuose lėtesnis nei Vector, išlaiko stabilesnį našumą dideliuose duomenų rinkiniuose.  
  - Efektyviai tvarkosi su trynimais ir perkelimais (splice), todėl Strategija 2 ir 3 skirtumai nėra tokie dideli.  

- **Split strategijų palyginimas**  
  - Strategija 1: dvigubas kopijavimas – lėčiausia ir atminties reikalaujanti.  
  - Strategija 2: vienas naujas konteineris su trynimu – efektyvesnė atminties atžvilgiu, bet Vector konteineryje trynimai lėtina procesą.  
  - Strategija 3: optimaliausia abiem konteinerių tipams – naudoja efektyvius algoritmus (Partition / Splice + Move) ir minimaliai apkrauna atmintį.  

**Išvada:** dideliems studentų duomenų kiekiams Strategija 3 yra rekomenduojama tiek Vector, tiek List konteineriams, o Vector konteineriuose būtina naudoti partition + move, o List – splice.
