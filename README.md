# **Programos spartos analizė**

Šioje ataskaitoje pateikiama analizė, lyginanti, kaip efektyviai veikia du skirtingi duomenų konteineriai – **Vector** ir **List** – apdorojant didelius studentų duomenų kiekius C++ kalboje.  
**Vector** tinkamesnis, kai duomenys išdėstyti nuosekliai atmintyje, o **List** – kai duomenys išsidėstę neapibrėžtai ar dažnai kinta jų tvarka.

---

## **1. Testavimo sistemos parametrai**

Visi testai atlikti naudojant tuos pačius duomenų failus. Lentelėse pateikti rezultatai gauti iš vieno bandymo, kuris atspindi vidutines reikšmes.

| **Parametras** | **Reikšmė** |
| :--- | :--- |
| **Procesorius (CPU)** | AMD Ryzen 7 8845HS w/ Radeon 780M Graphics 3.80 GHz |
| **Operatyvioji atmintis (RAM)** | 16 GB DDR4 |
| **Duomenų saugykla (SSD)** | 954 GB NVMe SSD |
| **Operacinė sistema** | Windows 11 |

---

## **2. Konteinerių testavimo rezultatai**

Laikai matuojami sekundėmis (s).  

### **2.1. Vector konteinerio rezultatai(sekundėmis)**

| Įrašų skaičius | Nuskaitymas ($T_{read}$) | Rūšiavimas ($T_{sort}$) | Skirstymas ($T_{split}$) | Įrašymas ($T_{write}$) | Bendrai ($T_{total}$) |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 000 | 0.0039 | 0.0023 | 0.0007 | 0.0294 | 0.0364 |
| 10 000 | 0.0401 | 0.0338 | 0.0066 | 0.0812 | 0.1613 |
| 100 000 | 0.3429 | 0.3952 | 0.0694 | 0.9813 | 1.7881 |
| 1 000 000 | 3.3160 | 5.1291 | 0.6863 | 6.7519 | 15.8832 |
| **10 000 000** | 37.3213 | **63.8957** | 6.5353 | 61.8754 | **169.6276** |

### **2.2. List konteinerio rezultatai(sekundėmis)**

| Įrašų skaičius | Nuskaitymas ($T_{read}$) | Rūšiavimas ($T_{sort}$) | Skirstymas ($T_{split}$) | Įrašymas ($T_{write}$) | Bendrai ($T_{total}$) |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 000 | 0.0046 | 0.0005 | 0.0119 | 0.0120 | 0.0180 |
| 10 000 | 0.0482 | 0.0053 | 0.0142 | 0.0946 | 0.1623 |
| 100 000 | 0.4479 | 0.0851 | 0.1586 | 0.9265 | 1.6181 |
| 1 000 000 | 4.3109 | **1.4320** | 1.6987 | 8.8138 | 16.2555 |
| **10 000 000** | 44.4090 | **16.8583** | 19.4405 | 72.2258 | **152.9336** |

---

## **3. Analizė ir išvados**

### **3.1. Didžiausias skirtumas – rūšiavimo laikas ($T_{sort}$)**

*Netikėtai geresnį rezultatą pasiekė „List“ konteineris.*  
Teoriškai **Vector** turėtų būti greitesnis, nes jo elementai išdėstyti nuosekliai atmintyje. Tačiau šiame eksperimente **List** rūšiavimo metu (16,85 s) buvo kelis kartus spartesnis nei **Vector** (63,89 s).  
Tikėtina priežastis – **atminties perkrovimas (paging)**, kai Vector konteineris, apdorodamas 10 milijonų įrašų, viršijo RAM ribas ir pradėjo naudoti lėtesnę diskinę atmintį.

---

### **3.2. Skirstymo kaštai ($T_{split}$)**

Abiejų konteinerių skirstymo etapas buvo gana lėtas. Tai rodo, kad programa atliko **kopijavimą** į naujus failus (*„vargsiukai“* ir *„kietiakai“*) vietoje duomenų perstūmimo atmintyje.  

---

### **3.3. Bendras našumo palyginimas**

Dėl rūšiavimo etapo vėlavimų **Vector** konteineris prarado dalį efektyvumo, todėl **List** pasiekė geresnį bendrą rezultatą su 10 milijonų įrašų (**152,9 s prieš 169,6 s**).  
Tai rodo, kad itin dideliuose duomenų kiekiuose **List** gali būti stabilesnis, kai **Vector** susiduria su atminties apribojimais ar fragmentacija.

---

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

## **5. Apibendrinimas**

Atliktas eksperimentas parodė, kad:  
- **Vector** yra efektyvus vidutinio dydžio duomenų kiekiams, tačiau jo našumas ženkliai mažėja, kai duomenų kiekis viršija RAM talpą.  
- **List** konteineris, nors paprastai lėtesnis mažesniuose testuose, išlaiko stabilesnį našumą dideliuose kiekiuose dėl mažesnių atminties perrašymo kaštų.  
