/*
    Problem 7: Particle Simulation: SoA vs. AoS [20 points]
Problem Description. You are simulating N point particles in 2D with positions (xi, yi) and
velocities (vx,i, vy,i). At each time step Δt, you advance
xi ← xi + vx,i Δt, yi ← yi + vy,i Δt.
Two memory layouts are common:
• AoS (Array of Structures): one array of Particle where each element stores {x,y,vx,vy}
together.
• SoA (Structure of Arrays): four parallel arrays x[], y[], vx[], vy[] storing each field
separately.
Example. Let N = 3. AoS stores:
P[0] = {x0, y0, vx0, vy0}, P[1] = {x1, y1, vx1, vy1}, P[2] = {x2, y2, vx2, vy2}.
SoA stores:
x = [x0, x1, x2], y = [y0, y1, y2], vx = [vx0, vx1, vx2], vy = [vy0, vy1, vy2].
A single update step adds Δt · vx[i] to x[i] and Δt · vy[i] to y[i] for each i. This assignment
compares the two layouts in code, tracing, and complexity.
*/

// ----- AoS -----
struct Particle {
    double x, y, vx, vy;
};

struct AoS {
    Particle* p; // array length N on the heap
    int N;
};

// Allocate AoS of size N and initialize from arrays (x[], y[], vx[], vy[]).
void aosInit(AoS& A, int N, 
            const double* x, 
            const double* y,
            const double* vx, 
            const double* vy) {
    A.N = N;
    A.p = new Particle[N];
    for (int i = 0; i < N; i++) {
        A.p[i].x = x[i];
        A.p[i].y = y[i];
        A.p[i].vx = vx[i];
        A.p[i].vy = vy[i];
    }
}

// Advance positions by dt: x += vx*dt, y += vy*dt for all particles.
void aosStep(AoS& A, double dt) {
    for (int i = 0; i < A.N; i++) {
        A.p[i].x += A.p[i].vx * dt;
        A.p[i].y += A.p[i].vy * dt;
    }
}

// Compute center of mass: returns (cx, cy) via refs.
void aosCenterOfMass(const AoS& A, double& cx, double& cy) {
    // Since all particles have equal mass, center of mass is just the average position.
    double sumX = 0.0;
    double sumY = 0.0;

    for (int i = 0; i < A.N; i++) {
        sumX += A.p[i].x;
        sumY += A.p[i].y;
    }

    cx = sumX / A.N;
    cy = sumY / A.N;
}

// Free AoS heap memory.
void aosFree(AoS& A) {
    delete A.p;
    A.p = nullptr;
    A.N = 0;
}

// ----- SoA -----
struct SoA {
    double *x, *y, *vx, *vy; // four arrays length N on the heap
    int N;
};

// Allocate SoA of size N and initialize from arrays (x[], y[], vx[], vy[]).
void soaInit(SoA& S, int N, 
            const double* x, 
            const double* y,
            const double* vx, 
            const double* vy) {
    S.N = N;
    S.x = new double[N];
    S.y = new double[N];
    S.vx = new double[N];
    S.vy = new double[N];
    for (int i = 0; i < N; i++) {
        S.x[i] = x[i];
        S.y[i] = y[i];
        S.vx[i] = vx[i];
        S.vy[i] = vy[i];
    }
}

// Advance positions by dt: x[i] += vx[i]*dt, y[i] += vy[i]*dt.
void soaStep(SoA& S, double dt) {
    for (int i = 0; i < S.N; i++) {
        S.x[i] += S.vx[i] * dt;
        S.y[i] += S.vy[i] * dt;
    }
}
// Compute center of mass: returns (cx, cy) via refs.
void soaCenterOfMass(const SoA& S, double& cx, double& cy) {
    // Since all particles have equal mass, center of mass is just the average position.
    double sumX = 0.0;
    double sumY = 0.0;

    for (int i = 0; i < S.N; i++) {
        sumX += S.x[i];
        sumY += S.y[i];
    }

    cx = sumX / S.N;
    cy = sumY / S.N;
}

// Free SoA heap memory.
void soaFree(SoA& S) {
    delete S.x;
    delete S.y;
    delete S.vx;
    delete S.vy;

    S.x = S.y = S.vx = S.vy = nullptr;
    S.N = 0;
}

// ----- Layout transform (optional helper pair) -----
// Copy A -> S (same N); Copy S -> A (same N). Assume targets allocated.
void aosToSoa(const AoS& A, SoA& S) {
    for (int i = 0; i < A.N; i++) {
        S.x[i] = A.p[i].x;
        S.y[i] = A.p[i].y;
        S.vx[i] = A.p[i].vx;
        S.vy[i] = A.p[i].vy;
    }
}
void soaToAos(const SoA& S, AoS& A) {
    for (int i = 0; i < S.N; i++) {
        A.p[i].x = S.x[i];
        A.p[i].y = S.y[i];
        A.p[i].vx = S.vx[i];
        A.p[i].vy = S.vy[i];
    }
}
