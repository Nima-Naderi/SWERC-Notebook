/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-28
 * Source: https://codeforces.com/contest/60/submission/84682398
 * Description: Basic operations on square matrices.
 * Usage: Matrix M = Matrix(2, 1)
 *  MAX.M[1][0]
 * Status: Tested on codeforces
 */
#pragma once

const ll MXZ = 100 + 10;
struct Matrix{
    int n, m; ll M[MXZ][MXZ];
    Matrix(int _n, int _m, ll num = 0){
        n = _n, m = _m;
        if(num == -1)
            for(int i = 0; i < n; i ++)
                for(int j = 0; j < m; j ++) M[i][j] = (i == j);
        else
            for(int i = 0; i < n; i ++)
                for(int j = 0; j < m; j ++) M[i][j] = num;
    }
    void Print(bool f = 0){
        cerr << "=======N.N=======\n";
        if(f) cerr << "Size : " << n << ' ' << m << '\n';
        for(int i = 0; i < n; i ++, cerr << '\n'){
            for(int j = 0; j < m; j ++) cerr << M[i][j] << ' ';
        }
        cerr << "=======N.N=======\n";
    }
    Matrix operator + (const Matrix &T){
        Matrix R = Matrix(n, m);
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < m; j ++)
                R.M[i][j] = (M[i][j] + T.M[i][j]) % Mod;
		return R;
    }
    Matrix operator * (const Matrix &T){
        Matrix R = Matrix(n, T.m);
        if(m != T.n){
			cerr << "Cannot * Matrices !" << '\n'; return R;
		}
        for(int i = 0; i < n; i ++){
            for(int j = 0; j < T.m; j ++){
                for(int k = 0; k < m; k ++){
                    ll now = (Ok(M[i][k]) * Ok(T.M[k][j])) % Mod;
                    R.M[i][j] = (R.M[i][j] + now) % Mod;
                }
            }
        }
        return R;
    }
    Matrix operator ^ (const ll t){
		Matrix R = Matrix(n, m, -1);
		if(n != m){
			cerr << "Cannot ^ Matrice with n != m !" << '\n'; return R;
		}
		if(t == 0) return R;
		Matrix T = Matrix(n, m);
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < m; j ++)
                T.M[i][j] = M[i][j];
		ll p = t;
		while(p){
			if(p & 1LL) R = R * T;
			T = (T * T), p /= 2;
		}
		return R;
	}
};
ll Fib(ll t){
    if(t == 1) return 1; Matrix M(2, 1), C(2, 2, 1);
    M.M[0][0] = M.M[1][0] = 1; C.M[1][1] = 0;
    C = (C ^ (t - 2)); M = (C * M); return M.M[0][0];
}