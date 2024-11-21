/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-21
 * Source: https://github.com/Nima-Naderi/Algonima/blob/master/DataStructures/RMQ.cpp
 * Description: Range Minimum Queries on an array (constant time).
 * Status: tested on codeforces
 */
#pragma once

int rmq[LOG][MXN], lg[MXN];
inline void BuildRmq(){
    for(int i = 1; i <= n; i ++) rmq[0][i] = A[i];
    for(int j = 1; j < LOG; j ++){
        for(int i = 1; i <= n; i ++){
            if(i < (1LL << j)) continue;
            rmq[j][i] = max(rmq[j - 1][i], rmq[j - 1][i - (1LL << (j - 1))]);
        }
    }
}
inline int Max(int l, int r){
    if(l == r) return rmq[0][l];
    if(r < l) swap(l, r);
    return max(rmq[lg[r - l + 1]][r], rmq[lg[r - l + 1]][l + (1LL << lg[r - l + 1]) - 1]);
}
inline void InitLog(){
	for(int i = 0; (1LL << i) < MXN; i ++) lg[(1LL << i)] = i;
	for(int i = 1; i < MXN; i ++)          lg[i] = max(lg[i - 1], lg[i]);
} //Call InitLog() & BuildRmq();
