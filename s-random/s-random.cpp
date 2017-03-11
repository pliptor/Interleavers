// (C) Oscar. Y. Takeshita 2017 
//
//  S-random interleavers 
//  http://ipnpr.jpl.nasa.gov/progress_report/42-122/122B.pdf
#include <algorithm>
#include <cassert>
#include <limits>
#include <random>
#include <vector>  

int main (int argc, char *argv[]) {
	std::random_device device;
	std::mt19937 generator(device());
	int32_t N; // interleaver length
	if (argc == 1 ) // set default interleaver length if no argument is given
		N = 128; 
	else
		if(argc == 2 )
			N = static_cast<int32_t>(atoi(argv[1]));
	if(N<=0 || N>(1<<20)) {
		fprintf(stderr, "Interleaver length must be betwen 1 and %d\n", (1<<20));
		return -1;
	}

	std::vector<int32_t> inter(N);
	/* S is the spread value */
	/* Typically S<sqrt(N/2) for convergence */
	int32_t S = floor(sqrt(static_cast<double>(N)/2.)), p;
	int32_t count, trials;
	fprintf(stderr, "Trying spread %d\n",S);

	while(true) {
		/* build pool */
		std::vector <uint32_t> pool;
		for(int32_t i = 0; i <N; i++)
			pool.push_back(i);
		/* shuffle */
		std::shuffle(pool.begin(), pool.end(), generator);
		count  = 0;
		trials = N;
		auto p = pool.begin(); // points to candidate in the pool
		//fprintf(stderr, "trying\n");
		while (!pool.empty() && trials--) {
			if (p == pool.end()) 
				p = pool.begin();
			bool found = true;
			// Here we do the S-interleaver constraint check
			for(auto p2 = inter.begin() + std::max(0, count-S); p2< inter.begin()+count; p2++) { // test if for all previous (domain) S values
				if(abs(*p - *p2) < S){ // the interleved (image) values follows constraint
					found = false;
					p++;
					break;
				}
			}
			if(found) {
				/* fprintf(stderr, "%d %d\n" ,count, pool[p]);  */
				inter[count] = *p;
				/* delete chosen element from the pool */
				pool.erase(p);
				count++;
				trials = N-count;
			}
		}
		if(pool.empty()) // terminate when interleaver is done (pool is empty)
			break;
	}
	/*
	   printf("%d 2\n",N);       // interleaver length and number of constituent codes 
	   for(int i = 0; i< N; i++) // information order for the first constituent code 
	   printf("%d\n",i);
	 */
	for(auto i : inter) { printf("%d\n", i); }; // information order for the second constintuent code
}
