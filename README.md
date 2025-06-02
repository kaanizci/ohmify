# Ohmify ⚡ – Ohm'sches Gesetz in C

Ohmify ist ein einfaches C-Projekt, das elektrische Größen mithilfe des Ohm'schen Gesetzes berechnet:

> **V = I × R**, **I = V ÷ R**, **R = V ÷ I**

## 🎯 Ziel

Das Projekt wurde als Einstieg in die C-Programmierung für Elektrotechnik-Studierende entwickelt. Es trainiert:
- Benutzereingaben mit `scanf`
- Formatierte Ausgaben mit `printf`
- Mathematische Berechnungen mit `float`
- Dateiein- und -ausgabe (`input.txt`, `output.txt`)
- Modularisierung mit Header-Dateien

## 🧪 Funktionen

- Berechnung von Spannung, Strom oder Widerstand über ein Menü
- Laden von mehreren Datensätzen aus einer Datei (`input.txt`)
- Speichern der Ergebnisse mit Zeitstempel in `output.txt`

## 🖥️ Verwendung

### 🔧 Kompilieren:

```bash
gcc main.c utils.c -o ohmify