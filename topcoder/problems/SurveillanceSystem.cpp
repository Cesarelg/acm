// BEGIN CUT HERE

// END CUT HERE
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cmath>
using namespace std;

vector<string> split( const string& s, const string& delim =" " ) {
    vector<string> res;
    string t;
    for ( int i = 0 ; i != s.size() ; i++ ) {
        if ( delim.find( s[i] ) != string::npos ) {
            if ( !t.empty() ) {
                res.push_back( t );
                t = "";
            }
        } else {
            t += s[i];
        }
    }
    if ( !t.empty() ) {
        res.push_back(t);
    }
    return res;
}

vector<int> splitInt( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<int> res;
    for ( int i = 0 ; i != tok.size(); i++ )
        res.push_back( atoi( tok[i].c_str() ) );
    return res;
}

// BEGIN CUT HERE
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))

template<typename T> void print( T a ) {
    cerr << a;
}
static void print( long long a ) {
    cerr << a << "L";
}
static void print( string a ) {
    cerr << '"' << a << '"';
}
template<typename T> void print( vector<T> a ) {
    cerr << "{";
    for ( int i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}
template<typename T> void eq( int n, T have, T need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
template<typename T> void eq( int n, vector<T> have, vector<T> need ) {
    if( have.size() != need.size() ) {
        cerr << "Case " << n << " failed: returned " << have.size() << " elements; expected " << need.size() << " elements.";
        print( have );
        print( need );
        return;
    }
    for( int i= 0; i < have.size(); i++ ) {
        if( have[i] != need[i] ) {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
// END CUT HERE
class SurveillanceSystem {
public:
    string getContainerInfo(string containers, vector <int> reports, int L) {
        string res;
        return res;
    }

};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        int reportsARRAY[] = {1, 2};
        vector <int> reports( reportsARRAY, reportsARRAY+ARRSIZE(reportsARRAY) );
        SurveillanceSystem theObject;
        eq(0, theObject.getContainerInfo("-X--XX", reports, 3),"??++++");
    }
    {
        int reportsARRAY[] = {2};
        vector <int> reports( reportsARRAY, reportsARRAY+ARRSIZE(reportsARRAY) );
        SurveillanceSystem theObject;
        eq(1, theObject.getContainerInfo("-XXXXX-", reports, 3),"???-???");
    }
    {
        int reportsARRAY[] = {3, 0, 2, 0};
        vector <int> reports( reportsARRAY, reportsARRAY+ARRSIZE(reportsARRAY) );
        SurveillanceSystem theObject;
        eq(2, theObject.getContainerInfo("------X-XX-", reports, 5),"++++++++++?");
    }
    {
        int reportsARRAY[] = {2, 1, 0, 1};
        vector <int> reports( reportsARRAY, reportsARRAY+ARRSIZE(reportsARRAY) );
        SurveillanceSystem theObject;
        eq(3, theObject.getContainerInfo("-XXXXX---X--", reports, 3),"???-??++++??");
    }
    {
        int reportsARRAY[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
        vector <int> reports( reportsARRAY, reportsARRAY+ARRSIZE(reportsARRAY) );
        SurveillanceSystem theObject;
        eq(4, theObject.getContainerInfo("-XX--X-XX-X-X--X---XX-X---XXXX-----X", reports, 7),"???++++?++++++++++++++++++++??????--");
    }
    return 0;
}
// END CUT HERE
