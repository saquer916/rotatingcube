# Rotating Cube in C

project i wanted to try out in c to leran without ai or tutorials

## Math

apologies in advance for the matrices as I don't know how to latex

### Individual Rotation Matrices
 
**Rotation around X-axis by angle `a`:**
 
$$R_x(a) = \begin{bmatrix} 1 & 0 & 0 \\ 0 & \cos a & -\sin a \\ 0 & \sin a & \cos a \end{bmatrix}$$
 
**Rotation around Y-axis by angle `b`:**
 
$$R_y(b) = \begin{bmatrix} \cos b & 0 & \sin b \\ 0 & 1 & 0 \\ -\sin b & 0 & \cos b \end{bmatrix}$$
 
**Rotation around Z-axis by angle `c`:**
 
$$R_z(c) = \begin{bmatrix} \cos c & -\sin c & 0 \\ \sin c & \cos c & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

---
 
### Combined Rotation Matrix
 
The three matrices are applied in the order **R = Rₓ(a) · R_y(b) · R_z(c)**, which means the point is first rotated around Z, then Y, then X. Multiplying them out gives the combined rotation matrix:
 
$$R = \begin{bmatrix} \cos b \cos c & -\cos b \sin c & \sin b \\ \cos a \sin c + \sin a \sin b \cos c & \cos a \cos c - \sin a \sin b \sin c & -\sin a \cos b \\ \sin a \sin c - \cos a \sin b \cos c & \sin a \cos c + \cos a \sin b \sin c & \cos a \cos b \end{bmatrix}$$
 
To rotate a 3D point **(x, y, z)** you compute:

$$\begin{bmatrix} x' \\ y' \\ z' \end{bmatrix} = R \cdot \begin{bmatrix} x \\ y \\ z \end{bmatrix}$$

## Perspective projection

After rotating, the 3D point is projected onto the 2D screen using **perspective division**. A camera offset (`distanceFromCam = 100`) is added to Z to simulate depth, and `ooz` ("one over z") scales objects that are farther away to appear smaller:
 
```c
z = changeZ(i, j, k) + distanceFromCam;
ooz = 1 / z;                                    // perspective scale factor
 
xp = (int)(width/2  + k1 * x * ooz * 2);       // *2 corrects for character aspect ratio
yp = (int)(height/2 + k1 * y * ooz);
```
 
The `* 2` on `xp` compensates for terminal characters being roughly **twice as tall as they are wide**.
 
---
 
## Z buffer
 
To correctly handle overlapping faces, a **z-buffer** (`zbuf`) tracks the depth of the closest point drawn at each screen position. A new point is only drawn if it is closer to the camera than whatever was drawn there before:
 
```c
if (ooz > zbuf[idx]) {    // ooz is larger when z is smaller (closer to camera)
    buf[idx] = ch;
    zbuf[idx] = ooz;
}
```
 
---

## Running Locally
 
### Prerequisites
 
You need a C compiler (`gcc` or `clang`) and a Unix-like terminal (Linux, macOS, or WSL on Windows).
 
Check if gcc is installed:
```bash
gcc --version
```
 
If not, install it:
 
**Ubuntu / Debian / WSL:**
```bash
sudo apt update && sudo apt install gcc
```
 
**macOS (via Homebrew):**
```bash
brew install gcc
```
 
---
 
### Build & Run
 
**1. Clone the repository:**
```bash
git clone https://github.com/your-username/rotating-cube.git
cd rotating-cube
```
 
**2. Compile the code:**
```bash
gcc -o cube cube.c -lm
```
> The `-lm` flag links the math library required for `sin()`, `cos()`, etc.
 
**3. Run it:**
```bash
./cube
```
 
**4. Stop it:**
 
Press `Ctrl + C` to exit.
 
---
 
