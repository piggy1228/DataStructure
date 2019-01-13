#include <vector>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include "image.h"
#include "visualization.h"


using namespace std;

//TO LINK IN THE HASHTABLE TO PREVENT COLLISIONS
class Node {
public:
    //default constructor
    Node(){
        next = NULL;
    }
    Point point;
    Node* next;
};

// ======================================================================
// Helper function to read the optional arguments and filenames from
// the command line.
void parse_arguments(int argc, char* argv[],
                     std::string& method, int& seed, int& table_size, float& compare,
                     std::vector<std::string>& filenames) {
    for (int i = 1; i < argc; i++) {
        if (argv[i] == std::string("-method")) {
            i++;
            assert (i < argc);
            method = argv[i];
            assert (method == "simple" || method == "hashtable");
        } else if (argv[i] == std::string("-seed")) {
            i++;
            assert (i < argc);
            seed = atoi(argv[i]);
            assert (seed >= 1);
        } else if (argv[i] == std::string("-table")) {
            i++;
            assert (i < argc);
            table_size = atoi(argv[i]);
            assert (table_size >= 1);
        } else if (argv[i] == std::string("-compare")) {
            i++;
            assert (i < argc);
            compare = atof(argv[i]);
            assert (compare > 0.0 && compare <= 1.0);
        } else {
            filenames.push_back(argv[i]);
        }
    }
    assert (filenames.size() > 0);
}


// ======================================================================
// This simple algorithm is rather inefficient, and may not find the
// largest overlapping subregion.  But it will find a subregion match
// of size seed x seed, if one exists.
void SimpleCompare(const Image<int>& a, const Image<int>& b,
                   Image<Color> &out, int which_color,int seed, float& percent,
                   std::vector<std::pair<BoundingBox,BoundingBox> >& regions) {
    
    // First, find a small seed that matches
    bool found = false;
    Point offset_a;
    Point offset_b;
    
    // Search over all possible points in image a
    for (int i = 0; i < a.Width()-seed && !found; i++) {
        for (int j = 0; j < a.Height()-seed && !found; j++) {
            // Search over all possible points in image b
            for (int i2 = 0; i2 < b.Width()-seed && !found; i2++) {
                for (int j2 = 0; j2 < b.Height()-seed && !found; j2++) {
                    bool match = true;
                    // Check for small seed match
                    for (int x = 0; x < seed && match; x++) {
                        for (int y = 0; y < seed && match; y++) {
                            if (a.GetPixel(i+x,j+y) != b.GetPixel(i2+x,j2+y)) {
                                match = false;
                            }
                        }
                    }
                    if (match) {
                        // break out of these loops!
                        HighlightSeed(out,which_color,Point(i,j),seed);
                        found = true;
                        offset_a = Point(i,j);
                        offset_b = Point(i2,j2);
                    }
                }
            }
        }
    }
    if (!found) {
        // no match between these images
        percent = 0.0;
        return;
    }
    
    int width = seed;
    int height = seed;
    
    //
    //
    // ASSIGNMENT:  COMPLETE THIS IMPLEMENTATION
    // First, expand the region match widthwise, until we hit the right
    // edge of one of the images or a mismatched pixel.
    
    bool same = true;
    int min_w = min((a.Width() - offset_a.x),(b.Width() - offset_b.x));
    for (int x = seed; x<min_w && same; x++) {
        for (int y = 0; y< seed && same; y++) {
            if (a.GetPixel(offset_a.x + x, y+offset_a.y) !=
                b.GetPixel(offset_b.x+x, y+offset_b.y)) {
                same = false;
            }
            else{
                width = x;
            }
        }
    }
    
    
    // Then, expand the region match heightwise, until we hit the top
    // edge of one of the images or a mismatched pixel.
    same = true;
    int min_h = min((a.Height() - offset_a.y),(b.Height() - offset_b.y));
    for (int x = 0; x<seed && same; x++) {
        for (int y = seed; y< min_h && same; y++) {
            if (a.GetPixel(offset_a.x + x, y+offset_a.y) !=
                b.GetPixel(offset_b.x+x, y+offset_b.y)) {
                same = false;
            }
            else{
                height = y;
            }
        }
    }
    
    
    BoundingBox bbox_a(offset_a,Point(offset_a.x+width,offset_a.y+height));
    BoundingBox bbox_b(offset_b,Point(offset_b.x+width,offset_b.y+height));
    regions.push_back(std::make_pair(bbox_a,bbox_b));
    // return fraction of pixels
    percent = bbox_a.Width()*bbox_a.Height() / float (a.Width()*a.Height());
}

//===========================================================================
//HASH TABLE FUNCTION
//===========================================================================
int SieveOfEratosthenes(int n)
{
    // Create a boolean array "prime[0..n]" and initialize
    // all entries it as true. A value in prime[i] will
    // finally be false if i is Not a prime, else true.
    //the function is modifided from website
    bool* prime =  new bool[n+1];
    int largestPrime = 0;
    for (int i =0; i<n+1; i++) {
        prime[i] = true;
    }
    for (int p=2; p*p<=n; p++)
    {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true)
        {
            // Update all multiples of p
            for (int i=p*2; i<=n; i += p)
                prime[i] = false;
        }
    }
    
    //FIND THE LARGEST PRIME
    for (int p=n; p>0; p--)
        if (prime[p]){
            largestPrime = p;
            break;
        }
    delete [] prime;
    return largestPrime;
}

/**
 combine each pixel into a integer within a block, remainder a prime which is
 a little bit smaller that table size so it can be seperated evenly in the table
 */
int HashFunction (int x,int y,const Image<int>& a,int seed,int prime) {
    int total = 0;
    for (int i=x; i<x+seed; i++) {
        for (int j=y; j<y+seed; j++) {
            total ^= a.GetPixel(i, j)<<13;
        }
    }
    return total%prime;
}

/**
 add used to add values in the hashtable. If there is collision, then there will
 have a link in the index,to link it at the end
 */
void add(Node* hashtable[], int index, int w, int h, string image){
    Node* tmp = new Node;
    tmp -> point = Point(w,h);
    tmp->next=hashtable[index];
    hashtable[index] = tmp;
}

/**
 helper function used to compare two images,if there pixels in one block are
 totally same
 */
bool samePixel(const Point &p1,const Image<int>& a,const Point &p2,const
               Image<int>& b,int seed){

    //each pixel in the block should be the same
    for (int i = 0; i<seed; i++) {
        for (int j = 0; j<seed; j++) {
            if (a.GetPixel(i+p1.x, j+p1.y)!= b.GetPixel(i+p2.x, j+p2.y)) {
                return false;//once there is different, return false
            }
        }
    }
    return true;
}


/*find the bound of the box to draew the box,to find the min,max width and height
 in the all the points that are same with another image to find out the correct
 bound point
 
 */
void bound(const vector<Point>& same,int &min_width,int &max_width,int
           &min_height,int &max_height){
    //initialize four  integer
    min_width = same[0].x;
    max_width = same[0].x;
    min_height = same[0].y;
    max_height = same[0].y;
    //go through all the point to find the max and min
    for (int i=0; i<same.size(); i++) {
        if (same[i].x<min_width) {
            min_width = same[i].x;
        }
        if (same[i].x>max_width) {
            max_width = same[i].x;
        }
        if (same[i].y<min_height) {
            min_height = same[i].y;
        }
        if (same[i].y > max_height) {
            max_height = same[i].y;
        }
    }
}

//===========================================================================
//HASH TABLE FUNCTION
/**
 first to create hashtable for each image,store one images' node,
 then go through the compare*table_size image,I go through it from the
 begin to the tablesize*compare,and each interval is 1 to let it go the front
 of the hashtable
.If ever found a collision, store the Point seperately in two vector for
 different images.Then go through the two vectors to find out if the blocks are
 the same, if the block same, then store them seperately in another vectors and
 highlight the same block in the first image. Finally find the bound and draw the
 bound box
 */
void createHashTable(const Image<int>& a,int seed,const int table_size,const string
                     &imageName,Node** &hashtable){
    for (int i = 0; i<table_size; i++) {
        hashtable[i] = NULL;
        //initialize all the position in the array
    }
    
    //create array as the hashtable
    int number = 0;
    //get the prime which is almost the table size
    int prime = SieveOfEratosthenes(table_size);
    
    
    //store all the block in imageA after hash
    for (int x = 0; x<a.Width()-seed; x++) {
        for (int y=0; y<a.Height()-seed; y++) {
            number = HashFunction(x,y,a,seed,prime);//hash function
            add(hashtable, number, x, y,imageName);//store it in the hashtable
        }
    }
}




void CompareHashtable(const Image<int>& a, const Image<int>& b,Image<Color> &out,
int which_color,int seed,float& percent, vector<pair<BoundingBox,BoundingBox> >&
regions,const int table_size, float compare, Node** &hashtableA,Node** & hashtableB){
    //COMPARE THE TWO HASH TABLE
    vector<Point> imageA;//store the collision point
    vector<Point> imageB;
    vector<Point> sameA;//store the exact same points
    vector<Point> sameB;
    int countA = 0;
    for (int i=0; i<table_size*compare; i++) {
        if (hashtableA[i] != NULL) {
            Node* p = hashtableA[i];
            Point pInsameNumber;
            //find and store the collision which might be same since they
            //hashed the same value
            while (p->next != NULL) {
                pInsameNumber = p->point;
                imageA.push_back(pInsameNumber);
                countA++;
                p=p->next;
            }
            if (hashtableB[i] != NULL) {
                Node* q = hashtableB[i];
                Point qInSameNumber;
                while (q -> next!= NULL) {
                    qInSameNumber = q -> point;
                    imageB.push_back(qInSameNumber);
                    q = q->next;
                }
            }
            //if there exist collision in the hashtable position
            if (imageA.size()>0 && imageB.size()>0) {
                for (int x=0; x<imageA.size(); x++) {
                    for (int y=0; y<imageB.size(); y++) {
                        //assert each point is the correct coordinate
                        assert(imageB[y].x<b.Width()-seed);
                        assert(imageB[y].y<b.Height()-seed);
                        if (samePixel(imageA[x], a, imageB[y], b, seed)) {
                            //highlight the same block in the imageA
                            HighlightSeed(out, which_color, imageA[x], seed);
                            sameA.push_back(imageA[x]);
                            sameB.push_back(imageB[y]);
                            
                        }
                    }
                }
            }
            imageA.clear();
            imageB.clear();
        }
    }
       //Assert that the number of blocks same
    //cout<<"SAMEA:"<<sameA.size()<<endl;
    assert(sameA.size() == sameB.size());
    if (sameA.size() == 0) {
        // no match between these images
        percent = 0.0;
        return;
    }
    //if there is same pixel in the two images
    int min_width = 0;
    int max_width = 0;
    int min_height = 0;
    int max_height = 0;
    //find where is the bound box
    bound(sameA, min_width, max_width, min_height, max_height);
    Point offset_a = Point(min_width,min_height);
    Point offset_a2 = Point(max_width+seed,max_height+seed);
    
    bound(sameB, min_width, max_width, min_height, max_height);
    Point offset_b = Point(min_width,min_height);
    Point offset_b2 = Point(max_width+seed,max_height+seed);
    //DRAW THE BOUND
    BoundingBox bbox_a(offset_a,offset_a2);
    BoundingBox bbox_b(offset_b,offset_b2);
    regions.push_back(std::make_pair(bbox_a,bbox_b));
    // return fraction of pixels
    percent = sameA.size()/float (countA);
}


// ======================================================================


int main(int argc, char* argv[]) {
    ///////////////////Timing part
     clock_t start, end;
     start = clock();
     ///////////////////
    std::string method = "simple";
    int seed = 5;
    int table_size = 1000000;
    float compare = 0.05;
    std::vector<std::string> filenames;
    parse_arguments(argc,argv,method,seed,table_size,compare,filenames);
    //=====================================================================
    //HASHTABLE METHOD
    if (method == "hashtable") {
        vector<Node**> AllHashTable;
        //CREATE A VECTOR TO STORE HASHTABLES FOR EACH IMAGE
        
        // Load all of the images
        std::vector<Image<int> > images(filenames.size());
        //store all the Point in the hash table
        for (int i = 0; i < filenames.size(); i++) {
            images[i].Load(filenames[i]);
            Node** hashtable = new Node*[table_size];
            createHashTable(images[i], seed, table_size, filenames[i],hashtable);
            AllHashTable.push_back(hashtable);
        }
        
        
        // Loop over all input images, comparing to every other input image
        for (int a = 0; a < filenames.size(); a++) {
            std::cout << filenames[a] << std::endl;
            // prepare a color visualization image for each input file
            Image<Color> out;
            InitializeOutputFile(images[a],out);
            int which_color = -1;
            for (int b = 0; b < filenames.size(); b++) {
                if (a == b) continue;
                which_color++;
    // Find the one (or more!) subregions that match between this pair of images
                std::vector<std::pair<BoundingBox,BoundingBox> > regions;
                float percent = 0.0;
                
                assert (method == "hashtable");
                // ASSIGNMENT:  IMPLEMENT THE HASHTABLE MATCHING ALGORITHM
                CompareHashtable(images[a],images[b],out,which_color,seed,percent,
                                 regions,table_size,compare,AllHashTable[a],
                                 AllHashTable[b]);
                
                std::cout << std::right << std::setw(7) << std::fixed <<
                std::setprecision(1)
                << 100.0 * percent << "% match with " << std::left << std::setw(20)
                << filenames[b];
                
                for (int i = 0; i < regions.size(); i++) {
                    std::cout << "   " << regions[i].first << " similar to " <<
                    regions[i].second;
                    // add the frame data to the visualization image
                    DrawBoundingBox(out,regions[i].first,which_color);
                }
                std::cout << std::endl;
                // Save the visualization image
                std::string f = "output_" + filenames[a].substr(0,
                                            filenames[a].size()-4) + ".ppm";
                out.Save(f);
                
            }
        }
        //DELETE ALL THE NODE ON THE HEAP TO PREVENT LEAK
        for (int j = 0 ; j<AllHashTable.size(); j++) {
            for (int i = 0; i<table_size; i++) {
                if (
                    AllHashTable[j][i] != NULL) {
                    Node* p = AllHashTable[j][i];
                    Node* tmp;
                    //delete all the node linked together with the same hash number
                    while (p->next) {
                        tmp = p;
                        p = p->next;
                        delete tmp;
                    }
                    delete p;
                }
            }
            delete []AllHashTable[j];
        }
    }

    
    //=========================================================================
    //simple methods
    else{
        assert(method =="simple");
        
        // Load all of the images
        std::vector<Image<int> > images(filenames.size());
        for (int i = 0; i < filenames.size(); i++) {
            images[i].Load(filenames[i]);
        }
        
        
        // Loop over all input images, comparing to every other input image
        for (int a = 0; a < filenames.size(); a++) {
            std::cout << filenames[a] << std::endl;
            // prepare a color visualization image for each input file
            Image<Color> out;
            InitializeOutputFile(images[a],out);
            int which_color = -1;
            for (int b = 0; b < filenames.size(); b++) {
                if (a == b) continue;
                which_color++;
                
    // Find the one (or more!) subregions that match between this pair of images
                std::vector<std::pair<BoundingBox,BoundingBox> > regions;
                float percent = 0.0;
                
                SimpleCompare(images[a],images[b],out,which_color,seed,
                              percent,regions);
                
                std::cout << std::right << std::setw(7) << std::fixed <<
                std::setprecision(1)
                << 100.0 * percent << "% match with " << std::left << std::setw(20)
                << filenames[b];
                
                for (int i = 0; i < regions.size(); i++) {
                    std::cout << "   " << regions[i].first << " similar to " <<
                    regions[i].second;
                    // add the frame data to the visualization image
                    DrawBoundingBox(out,regions[i].first,which_color);
                }
                std::cout << std::endl;
                // Save the visualization image
                std::string f = "output_" + filenames[a].substr(0,
                                            filenames[a].size()-4) + ".ppm";
                out.Save(f);
                
            }
        }
    }
    ////////////////////////////////////////////////////////////////////Timing
     end = clock();
     static double time_consumed = (double)(end - start) / CLOCKS_PER_SEC;
     cout << "Time: " << time_consumed << " s" <<endl;
     ////////////////////////////////////////////////////////////////////
}
