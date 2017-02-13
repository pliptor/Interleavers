/* (C) Oscar. Y. Takeshita 2017 */
#include <vector>
#include <algorithm>
typedef unsigned int uint32;
using namespace std;
class Random {
	public:
		Random() = default;
		Random(std::mt19937::result_type seed) : eng(seed) {}
		uint32 DrawNumber(uint32 min, uint32 max) {
			return std::uniform_int_distribution<uint32>{min, max}(eng);
		}
	private:        
		std::mt19937 eng{std::random_device{}()};
};

int main (int argc, char *argv[]) {
	int N;
	if (argc == 1 ) 
		N = 1024;
	else
		if(argc == 2 )
			N = atoi(argv[1]);

	vector<int> inter(N);
	Random r;
	/* S is the spread value */
	/* Typically choose S<sqrt(N/2) */
	int S = floor(sqrt((double)N/2.)), p;
	int count, point, trials;
	bool done = false;
	bool found;
	fprintf(stderr,"Trying spread %d\n",S);

	while(!done) {
		/* build pool */
		vector <int> pool;
		for(int i = 0; i <N; i++)
			pool.push_back(i);
		count  = 0;
		trials = 0;
		//fprintf(stderr,"trying\n");
		while (count<N) {
			/* choose index */
			p = r.DrawNumber(0,pool.size()-1);
			/* check if the selected integer is within
			   +/-s of all previously selected */
			found = true;
			for(point = count-S; point<count; point++) {
				if((point >-1) && (abs(pool[p]-inter[point])<S)){
					found = false;
					break;
				}
			}
			if(found) {
				/* fprintf(stderr,"%d %d\n",count,pool[p]);  */
				inter[count] = *(pool.begin()+p);
				/* delete chosen element from the pool */
				pool.erase(pool.begin()+p);
				count++;
				done = (count == N);
			}
			trials++;
			if(trials>100*N)
				break;
			if(done)
				break;
		}
	}
	/*
	   printf("%d 2\n",N);       // interleaver length and number of constituent codes 
	   for(int i = 0; i< N; i++) // information order for the first constituent code 
	   printf("%d\n",i);
	 */
	for_each(inter.begin(), inter.end(), [](int p) { // information order for the second constintuent code
			printf("%d\n",p);
			});
}
