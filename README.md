<p align="left">
  <a href="#--------cpp06--">🇬🇧 English</a> |
  <a href="#--------cpp06---1">🇫🇷 Français</a>
</p>

<h1 align="center">
  <br>
  <img src="https://i.ibb.co/MkL14CvZ/logo-cpp-bonus.png" alt="C++ logo" width="150">
  <br>
  cpp06
  <br>
</h1>

<h4 align="center"><em>C++ Module 06 — C++ casts: static, reinterpret, and dynamic conversions.</em></h4>

<p align="center">
  <img src="https://img.shields.io/badge/exercises-3-orange">
  <img src="https://img.shields.io/badge/C%2B%2B-100%25-blue">
  <img src="https://img.shields.io/badge/Grade-100%2F100-brightgreen">
  <img src="https://img.shields.io/badge/standard-C%2B%2B98-informational">
</p>

<p align="center">
  <a href="./subject.md">Subject</a> |
  <a href="#-project-overview">Overview</a> •
  <a href="#-code-architecture-and-organization">Architecture</a> •
  <a href="#-operating">Operating</a> •
  <a href="#%EF%B8%8F-compiling-and-testing">Compiling</a>
</p>

---

## 📌 **Project overview**

**cpp06** is the sixth C++ module of the 42 Common Core. It focuses on **C++ casts** and type conversions between scalar types, raw memory addresses, and polymorphic objects.

The project is split into **3 independent exercises**, each dedicated to a specific cast. All code complies with **C++98**.

### 1. Exercise 00 — Conversion of scalar types ✅

The `ScalarConverter` class provides a single static method `convert(literal)`:

* Detects the type of a C++ literal passed as a string (`char`, `int`, `float`, `double`)
* Parses the literal, then **explicitly converts** it to the three other scalar types using `static_cast`
* Displays results in the format: `char: …`, `int: …`, `float: …`, `double: …`
* Handles pseudo-literals: `nan`, `nanf`, `+inf`, `-inf`, `+inff`, `-inff`
* Prints `impossible`, `Non displayable`, or the converted value when appropriate

### 2. Exercise 01 — Serialization ✅

The `Serializer` class converts a pointer to a raw integer and back using `reinterpret_cast`:

* `serialize(Data*)` → `uintptr_t` (raw address as an unsigned integer)
* `deserialize(uintptr_t)` → `Data*` (pointer restored from the integer)
* `Data` is a non-empty structure with `number`, `name`, and `active` members
* The deserialized pointer must compare equal to the original and remain usable

### 3. Exercise 02 — Identify real type ✅

Polymorphic type identification using `dynamic_cast` (without `<typeinfo>`):

* `Base` has a **public virtual destructor** only
* `A`, `B`, `C` are empty classes publicly inheriting from `Base`
* `generate()` randomly creates an `A`, `B`, or `C` and returns a `Base*`
* `identify(Base*)` prints `"A"`, `"B"`, or `"C"` (checks for `NULL` cast result)
* `identify(Base&)` prints the real type using `try` / `catch` (no pointers allowed inside)

### Conversion rules ⚠️

* **ex00**: `static_cast` for scalar conversions; implicit promotion allowed only where natural
* **ex01**: `reinterpret_cast` in both directions (pointer ↔ integer)
* **ex02**: `dynamic_cast` for runtime type identification; `<typeinfo>` is **forbidden**

---

## 📂 **Code architecture and organization**

```
cpp06/
├── ex00/   ScalarConverter
├── ex01/   Serializer + Data
├── ex02/   Base, A, B, C + identify / generate
├── subject.md
└── evaluation_sheet.md
```

#### 🔹 `ScalarConverter` (ex00)

| Method | Description |
|--------|-------------|
| `convert(literal)` | Detects literal type, parses it, converts to `char` / `int` / `float` / `double`, prints results |

* Non-instantiable utility class (private OCF)
* CLI usage: `./convert <literal>` (subject examples: `0`, `nan`, `42.0f`)

#### 🔹 `Data` (ex01)

| Member | Type | Description |
|--------|------|-------------|
| `number` | `int` | Numeric field |
| `name` | `std::string` | String field |
| `active` | `bool` | Boolean flag |

#### 🔹 `Serializer` (ex01)

| Method | Description |
|--------|-------------|
| `serialize(Data*)` | `reinterpret_cast<uintptr_t>(ptr)` — pointer to raw address |
| `deserialize(uintptr_t)` | `reinterpret_cast<Data*>(raw)` — address back to pointer |

* Non-instantiable utility class (private OCF)

#### 🔹 `Base`, `A`, `B`, `C` (ex02)

| Class | Description |
|-------|-------------|
| `Base` | Abstract polymorphic base; public virtual destructor only (no OCF required) |
| `A` / `B` / `C` | Empty concrete classes publicly inheriting from `Base` (no OCF required) |

#### 🔹 Identification functions (ex02)

| Function | Description |
|----------|-------------|
| `generate()` | Randomly `new`s an `A`, `B`, or `C`; returns `Base*` |
| `identify(Base*)` | `dynamic_cast` to `A*` / `B*` / `C*`; checks `NULL` on failure |
| `identify(Base&)` | `dynamic_cast` to `A&` / `B&` / `C&`; catches `std::exception&` on failure |

---

## 🏛 **Operating**

### 🔸 **static_cast (ex00)**

`static_cast` performs **compile-time-checked** conversions between related types. In ex00, once the literal type is detected and parsed, values are explicitly cast to the other scalar types:

```cpp
char c = static_cast<char>(static_cast<int>(parsedValue));
float f = static_cast<float>(parsedValue);
double d = static_cast<double>(parsedValue);
```

**Output rules:**

| Case | `char` output |
|------|---------------|
| `NaN` / `inf` | `impossible` |
| Value ∉ [0, 127] | `impossible` |
| Non-printable (e.g. `0`) | `Non displayable` |
| Printable ASCII | `'X'` |

`int` is `impossible` on overflow, `NaN`, or `inf`. Float output uses an `f` suffix (`42.0f`); double uses decimal notation (`42.0`).

### 🔸 **reinterpret_cast (ex01)**

`reinterpret_cast` reinterprets the **bit pattern** of a value without changing it — used here to store a pointer as an integer and restore it:

```cpp
uintptr_t raw = Serializer::serialize(&data);
Data*       ptr = Serializer::deserialize(raw);
// ptr == &data
```

This is **not** a numeric conversion: the same memory address round-trips through an integer representation. The `Data` object remains readable and writable through the restored pointer.

### 🔸 **dynamic_cast (ex02)**

`dynamic_cast` identifies the **real runtime type** of a polymorphic object through a base-class pointer or reference. It requires a **virtual function** in the base class (here, the virtual destructor).

**Pointer version** — returns `NULL` on failure:

```cpp
if (dynamic_cast<A*>(p) != 0)
    std::cout << "A" << std::endl;
```

**Reference version** — throws on failure (caught via `std::exception&`):

```cpp
try {
    (void)dynamic_cast<A&>(p);
    std::cout << "A" << std::endl;
} catch (std::exception& e) { /* not an A */ }
```

`<typeinfo>` and `std::type_info` are **forbidden** — identification relies solely on `dynamic_cast` behaviour.

### 🔸 **Type detection order (ex00)**

Literal detection matters — especially for pseudo-literals ending in `f`:

1. Char literal (`'a'`)
2. Float pseudo-literals (`nanf`, `+inff`, `-inff`)
3. Double pseudo-literals (`nan`, `+inf`, `-inf`) — checked **before** the `f` suffix rule
4. Float (ends with `f`)
5. Double (contains `.`)
6. Integer (default)

---

## ⚙️ **Compiling and testing**

Each exercise is **independent** and has its own `Makefile`. Compile and run from the exercise directory.

### 🔧 Compiling

| Exercise | Binary | Command |
|----------|--------|---------|
| ex00 | `convert` | `cd ex00 && make` |
| ex01 | `serializer` | `cd ex01 && make` |
| ex02 | `identify` | `cd ex02 && make` |

```bash
make        # compile
make re     # full rebuild
make fclean # remove binary and object files
```

Compiler flags: `c++ -Wall -Wextra -Werror -std=c++98`

---

### ▶️ Use and execution

- #### ✅ Exercise 00 — `./convert`

  ```bash
  cd ex00 && make && ./convert 0
  cd ex00 && ./convert nan
  cd ex00 && ./convert 42.0f
  ```

  Without arguments, runs the full test suite:

  ```bash
  cd ex00 && ./convert
  ```

  Tests cover: subject examples, char/int/float/double literals, pseudo-literals, overflow, invalid input.

- #### ✅ Exercise 01 — `./serializer`

  ```bash
  cd ex01 && make && ./serializer
  ```

  Tests cover: pointer equality after round-trip, readable `Data` members, same-object memory, distinct objects, heap allocation (`new`/`delete`), `NULL` pointer.

  * Check memory leaks (macOS): `leaks -atExit -- ./serializer`

- #### ✅ Exercise 02 — `./identify`

  ```bash
  cd ex02 && make && ./identify
  ```

  Tests cover: `identify(Base*)` and `identify(Base&)` on `A`/`B`/`C`, polymorphism, `generate()` × 10, `NULL` pointer safety.

  * Check memory leaks (macOS): `leaks -atExit -- ./identify`

#### Example — subject output (ex00)

```bash
./convert 0
# char: Non displayable
# int: 0
# float: 0.0f
# double: 0.0

./convert nan
# char: impossible
# int: impossible
# float: nanf
# double: nan

./convert 42.0f
# char: '*'
# int: 42
# float: 42.0f
# double: 42.0
```

---

<h1 align="center">
  <br>
  <img src="https://i.ibb.co/MkL14CvZ/logo-cpp-bonus.png" alt="logo C++" width="150">
  <br>
  cpp06
  <br>
</h1>

<h4 align="center"><em>Module C++ 06 — C++ casts : conversions static, reinterpret et dynamic.</em></h4>

<p align="center">
  <img src="https://img.shields.io/badge/exercices-3-orange">
  <img src="https://img.shields.io/badge/C%2B%2B-100%25-blue">
  <img src="https://img.shields.io/badge/Note-100%2F100-brightgreen">
  <img src="https://img.shields.io/badge/standard-C%2B%2B98-informational">
</p>

<p align="center">
  <a href="./subject.md">Sujet</a> |
  <a href="#-aperçu-du-projet">Aperçu</a> •
  <a href="#-architecture-et-organisation-du-code">Architecture</a> •
  <a href="#-fonctionnement">Fonctionnement</a> •
  <a href="#%EF%B8%8F-compilation-et-tests">Compilation</a>
</p>

---

## 📌 **Aperçu du projet**

**cpp06** est le sixième module C++ du Common Core de 42. Il porte sur les **casts C++** et les conversions de types entre scalaires, adresses mémoire brutes et objets polymorphes.

Le projet est découpé en **3 exercices indépendants**, chacun dédié à un cast spécifique. Tout le code respecte le standard **C++98**.

### 1. Exercice 00 — Conversion de types scalaires ✅

La classe `ScalarConverter` expose une seule méthode statique `convert(literal)` :

* Détecte le type d'un littéral C++ passé en string (`char`, `int`, `float`, `double`)
* Parse le littéral, puis le convertit **explicitement** vers les 3 autres types scalaires via `static_cast`
* Affiche les résultats au format : `char: …`, `int: …`, `float: …`, `double: …`
* Gère les pseudo-littéraux : `nan`, `nanf`, `+inf`, `-inf`, `+inff`, `-inff`
* Affiche `impossible`, `Non displayable` ou la valeur convertie selon les cas

### 2. Exercice 01 — Sérialisation ✅

La classe `Serializer` convertit un pointeur en entier brut et inversement via `reinterpret_cast` :

* `serialize(Data*)` → `uintptr_t` (adresse brute sous forme d'entier non signé)
* `deserialize(uintptr_t)` → `Data*` (pointeur restauré depuis l'entier)
* `Data` est une structure non vide avec les champs `number`, `name` et `active`
* Le pointeur désérialisé doit être égal à l'original et rester utilisable

### 3. Exercice 02 — Identifier le vrai type ✅

Identification du type réel à l'exécution via `dynamic_cast` (sans `<typeinfo>`) :

* `Base` possède uniquement un **destructeur virtuel public**
* `A`, `B`, `C` sont des classes vides héritant publiquement de `Base`
* `generate()` crée aléatoirement un `A`, `B` ou `C` et renvoie un `Base*`
* `identify(Base*)` affiche `"A"`, `"B"` ou `"C"` (vérifie le `NULL` si le cast échoue)
* `identify(Base&)` affiche le vrai type avec `try` / `catch` (aucun pointeur autorisé dans la fonction)

### Règles de conversion ⚠️

* **ex00** : `static_cast` pour les conversions scalaires ; promotion implicite autorisée uniquement là où elle est naturelle
* **ex01** : `reinterpret_cast` dans les deux sens (pointeur ↔ entier)
* **ex02** : `dynamic_cast` pour l'identification à l'exécution ; `<typeinfo>` est **interdit**

---

## 📂 **Architecture et organisation du code**

```
cpp06/
├── ex00/   ScalarConverter
├── ex01/   Serializer + Data
├── ex02/   Base, A, B, C + identify / generate
├── subject.md
└── evaluation_sheet.md
```

#### 🔹 `ScalarConverter` (ex00)

| Méthode | Description |
|---------|-------------|
| `convert(literal)` | Détecte le type du littéral, le parse, convertit vers `char` / `int` / `float` / `double`, affiche les résultats |

* Classe utilitaire non instanciable (OCF privée)
* Usage CLI : `./convert <litteral>` (exemples du sujet : `0`, `nan`, `42.0f`)

#### 🔹 `Data` (ex01)

| Membre | Type | Description |
|--------|------|-------------|
| `number` | `int` | Champ numérique |
| `name` | `std::string` | Champ texte |
| `active` | `bool` | Indicateur booléen |

#### 🔹 `Serializer` (ex01)

| Méthode | Description |
|---------|-------------|
| `serialize(Data*)` | `reinterpret_cast<uintptr_t>(ptr)` — pointeur vers adresse brute |
| `deserialize(uintptr_t)` | `reinterpret_cast<Data*>(raw)` — adresse reconvertie en pointeur |

* Classe utilitaire non instanciable (OCF privée)

#### 🔹 `Base`, `A`, `B`, `C` (ex02)

| Classe | Description |
|--------|-------------|
| `Base` | Base polymorphe ; destructeur virtuel public uniquement (pas d'OCF requise) |
| `A` / `B` / `C` | Classes concrètes vides héritant publiquement de `Base` (pas d'OCF requise) |

#### 🔹 Fonctions d'identification (ex02)

| Fonction | Description |
|----------|-------------|
| `generate()` | Crée aléatoirement un `A`, `B` ou `C` avec `new` ; renvoie un `Base*` |
| `identify(Base*)` | `dynamic_cast` vers `A*` / `B*` / `C*` ; vérifie `NULL` en cas d'échec |
| `identify(Base&)` | `dynamic_cast` vers `A&` / `B&` / `C&` ; attrape `std::exception&` en cas d'échec |

---

## 🏛 **Fonctionnement**

### 🔸 **static_cast (ex00)**

`static_cast` effectue des conversions **vérifiées à la compilation** entre types liés. En ex00, une fois le littéral détecté et parsé, les valeurs sont castées explicitement vers les autres types scalaires :

```cpp
char c = static_cast<char>(static_cast<int>(parsedValue));
float f = static_cast<float>(parsedValue);
double d = static_cast<double>(parsedValue);
```

**Règles d'affichage :**

| Cas | sortie `char` |
|-----|---------------|
| `NaN` / `inf` | `impossible` |
| Valeur ∉ [0, 127] | `impossible` |
| Non affichable (ex. `0`) | `Non displayable` |
| ASCII affichable | `'X'` |

`int` affiche `impossible` en cas d'overflow, `NaN` ou `inf`. Le float utilise le suffixe `f` (`42.0f`) ; le double la notation décimale (`42.0`).

### 🔸 **reinterpret_cast (ex01)**

`reinterpret_cast` réinterprète le **motif de bits** d'une valeur sans le modifier — ici pour stocker un pointeur sous forme d'entier et le restaurer :

```cpp
uintptr_t raw = Serializer::serialize(&data);
Data*       ptr = Serializer::deserialize(raw);
// ptr == &data
```

Ce n'est **pas** une conversion numérique : la même adresse mémoire fait l'aller-retour via une représentation entière. L'objet `Data` reste lisible et modifiable via le pointeur restauré.

### 🔸 **dynamic_cast (ex02)**

`dynamic_cast` identifie le **vrai type à l'exécution** d'un objet polymorphe via un pointeur ou une référence de classe de base. Il nécessite une **fonction virtuelle** dans la classe de base (ici, le destructeur virtuel).

**Version pointeur** — renvoie `NULL` en cas d'échec :

```cpp
if (dynamic_cast<A*>(p) != 0)
    std::cout << "A" << std::endl;
```

**Version référence** — lève une exception en cas d'échec (attrapée via `std::exception&`) :

```cpp
try {
    (void)dynamic_cast<A&>(p);
    std::cout << "A" << std::endl;
} catch (std::exception& e) { /* ce n'est pas un A */ }
```

`<typeinfo>` et `std::type_info` sont **interdits** — l'identification repose uniquement sur le comportement de `dynamic_cast`.

### 🔸 **Ordre de détection des types (ex00)**

L'ordre de détection compte — surtout pour les pseudo-littéraux finissant par `f` :

1. Littéral char (`'a'`)
2. Pseudo-littéraux float (`nanf`, `+inff`, `-inff`)
3. Pseudo-littéraux double (`nan`, `+inf`, `-inf`) — testés **avant** la règle du suffixe `f`
4. Float (finit par `f`)
5. Double (contient `.`)
6. Entier (par défaut)

---

## ⚙️ **Compilation et tests**

Chaque exercice est **indépendant** et possède son propre `Makefile`. Compiler et exécuter depuis le dossier de l'exercice.

### 🔧 Compilation

| Exercice | Binaire | Commande |
|----------|---------|----------|
| ex00 | `convert` | `cd ex00 && make` |
| ex01 | `serializer` | `cd ex01 && make` |
| ex02 | `identify` | `cd ex02 && make` |

```bash
make        # compiler
make re     # recompilation complète
make fclean # supprime binaire et fichiers objets
```

Flags : `c++ -Wall -Wextra -Werror -std=c++98`

---

### ▶️ Utilisation et exécution

- #### ✅ Exercice 00 — `./convert`

  ```bash
  cd ex00 && make && ./convert 0
  cd ex00 && ./convert nan
  cd ex00 && ./convert 42.0f
  ```

  Sans argument, lance la suite de tests complète :

  ```bash
  cd ex00 && ./convert
  ```

  Tests : exemples du sujet, littéraux char/int/float/double, pseudo-littéraux, overflow, entrée invalide.

- #### ✅ Exercice 01 — `./serializer`

  ```bash
  cd ex01 && make && ./serializer
  ```

  Tests : égalité des pointeurs après round-trip, membres `Data` lisibles, même objet en mémoire, objets distincts, allocation tas (`new`/`delete`), pointeur `NULL`.

  * Vérifier les fuites mémoire (macOS) : `leaks -atExit -- ./serializer`

- #### ✅ Exercice 02 — `./identify`

  ```bash
  cd ex02 && make && ./identify
  ```

  Tests : `identify(Base*)` et `identify(Base&)` sur `A`/`B`/`C`, polymorphisme, `generate()` × 10, sécurité pointeur `NULL`.

  * Vérifier les fuites mémoire (macOS) : `leaks -atExit -- ./identify`

#### Exemple — sortie du sujet (ex00)

```bash
./convert 0
# char: Non displayable
# int: 0
# float: 0.0f
# double: 0.0

./convert nan
# char: impossible
# int: impossible
# float: nanf
# double: nan

./convert 42.0f
# char: '*'
# int: 42
# float: 42.0f
# double: 42.0
```
