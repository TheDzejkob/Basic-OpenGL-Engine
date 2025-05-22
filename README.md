# Simle OpenGL Engine

Tento projekt je jednoduchý OpenGL engine napsaný v C++14, který demonstruje základní práci s OpenGL, GLFW a GLAD. Engine vykresluje základní tvary pomocí vertex a fragment shaderů načítaných ze souborů.

---

## Závislosti

- **GLFW** – správa oken a vstupů  
- **GLAD** – načítání OpenGL funkcí  
- **C++14 kompatibilní překladač**

---

## Jak to funguje

1. **Inicializace**  
   Aplikace inicializuje GLFW, nastaví OpenGL kontext (verze 3.3 Core) a načte GLAD.

2. **Načtení shaderů**  
   Shader kódy jsou načteny ze souborů `src/Vertex_shader.frag` (vertex shader) a `src/fragment_shader.frag` (fragment shader).  
   _Poznámka: Vertex shader je uložen v souboru s příponou `.frag`, což je neobvyklé, ale funkčně nezávadné._

3. **Kompilace a linkování shaderů**  
   Shadery jsou zkompilovány a slinkovány do jednoho shader programu.

4. **Nastavení dat pro vykreslení**  
   - Definice vrcholů (vertices) a indexů (indices) pro čtverec složený ze dvou trojúhelníků.  
   - Vytvoření a nastavení VAO (Vertex Array Object), VBO (Vertex Buffer Object) a EBO (Element Buffer Object).  
   - Nastavení atributů vrcholů.

5. **Render loop**  
   - Vymazání obrazovky a nastavení barvy pozadí.  
   - Aktivace shader programu a VAO.  
   - Vykreslení objektu pomocí `glDrawElements`.  
   - Zpracování vstupů a výměna bufferů.

6. **Ukončení**  
   Uvolnění všech alokovaných OpenGL objektů a ukončení GLFW.

---

## Shader soubory

- **Vertex_shader.frag**  
  Obsahuje vertex shader, který transformuje pozici vrcholu do clip-space.

- **fragment_shader.frag**  
  Definuje barvu fragmentu (pixelu) – v tomto případě oranžovou.

---

## Spuštění

1. Přeložte projekt pomocí CMake nebo Visual Studia.  
2. Ujistěte se, že soubory shaderů jsou ve složce `src/`.  
3. Spusťte binárku. Mělo by se zobrazit okno s vykresleným čtvercem (složeným ze dvou trojúhelníků).

---

## Poznámky

- Pokud se nic nevykresluje, zkontrolujte konzoli na chyby kompilace/linkování shaderů.  
- Pro správné fungování musí být grafické ovladače aktuální a podporovat OpenGL 3.3+.  
