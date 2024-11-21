ll rand(ll l, ll r) { return l + rand() % (r - l + 1); }
int32_t main(int argc, char* argv[]){
	srand(atoi(argv[1]));
	ll n = rand(2, 20); //input size
    cout << "TEST" << '\n';
}
