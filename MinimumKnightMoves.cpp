#include <bits/stdc++.h>
using namespace std;
using ll=long long int;
const ll MOD=1000000007;
vector<bool> visited(65);
vector<bool> prime(1000001, true);
unordered_map<ll, ll> dist;
unordered_map<ll, ll> par;
vector<vector<ll>> vertices(65);
ll to_number(string s)
{
    ll n=s[1]-48;
    n = n + 8*(s[0]-'a');
    return n;
}
string to_str(ll n)
{
    if(n%8==0)
    {
        string ch2(1, (char)56), ch1(1, (char)(n/8 + 96));
        return ch1+ch2;
    }
    string ch2(1, (char)(n%8 + 48)), ch1(1, (char)(n/8 + 97));
    return ch1+ch2;
}
bool BFS(ll source, ll dest)
{
    visited[source]=true;
    dist[source]=0;
    list<ll> queue;
    queue.push_back(source);
    while(!queue.empty())
    {
        ll c=queue.front();
        ll n=vertices[c].size();
        queue.pop_front();
        for(ll i=0; i<n; i++)
        {
            if(visited[vertices[c][i]]==false)
            {
                par[vertices[c][i]]=c;
                visited[vertices[c][i]]=true;
                dist[vertices[c][i]]=dist[c]+1;
                queue.push_back(vertices[c][i]);
                if(vertices[c][i]==dest)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
ll getPath(ll source, ll dest)
{
    bool path_exist=BFS(source, dest);
    if(path_exist==false)
    {
        cout<<"No way to get to the destination!!\n";
        return -1;
    }
    vector<ll> path;
    path.push_back(dest);
    ll cur=par[path[0]];
    while(cur!=source)
    {
        path.push_back(cur);
        cur=par[cur];
    }
    path.push_back(source);
    ll n=path.size();
    cout<<"The path is: ";
    for(ll i=n-1; i>=1; i--)
    {
        cout<<to_str(path[i])<<" -> ";
    }
    cout<<to_str(path[0])<<"\n";
    return dist[dest];
}
void sieve(ll n=1000000, bool specify=false)
{
    for(int i=2; i*i<=n; i++)
    {
        if(prime[i])
        {
            for(int j=i*i; j<=n; j+=i)
            {
                prime[j]=false;
            }
        }
    }
    if(!specify)
    {
        prime[0]=false;
        prime[1]=false;
    }
}

ll power(ll a, ll b, ll c=MOD)
{
    if(b==0)
    {
        return 1;
    }
    ll temp=power(a, b/2, c);
    temp=(temp*temp)%c;
    a%=c;
    if(b%2)
    {
        return (a*temp)%c;
    }
    return temp;
}

ll gcd(ll, ll);

/*ll C(ll n, ll r, ll m=MOD)
{
    if((n-r)<r)
    {
        r=n-r;
    }
    if(r==0)
    {
        return 1;
    }
    ll p=1, k=1;
    while(r)
    {
        ll num=n%m;
        ll denom=((m/r)*(-1/(m%r)))m;
        p=(p*num*denom)%m;
        n--;
        r--;
    }
    return p;
}*/

ll gcd(ll a, ll b)
{
    if(a==0)
    {
        return b;
    }
    return gcd(b%a, a);
}

bool isPrime(ll n)
{
    for(int i=2; i*i<=n; i++)
    {
        if(n%i)
        {
            continue;
        }
        return false;
    }
    return true;
}

vector<ll> to_binary(ll n)
{
    ll size = ceil(log(n)/log(2))+1;
    vector<ll> a(size, 0);
    ll i=size-1;
    while(n>0&&i>=0)
    {
        a[i]=n%2;
        n/=2;
        i--;
    }
    return a;
}

int main()
{
	unordered_map<string, vector<string>> blocks;
	for(int i=97; i<=104; i++)
	{
	    for(int j=49; j<=56; j++)
	    {
	        string ch1(1, (char)i), ch2(1, (char)j);
	        string node=ch1+ch2;
	        if(i+2<=104)
	        {
	            if(j+1<=56)
	            {
	                string ans1(1, (char)(i+2)), ans2(1, (char)(j+1));
	                string ans=ans1+ans2;
	                blocks[node].push_back(ans);
	            }
	            if(j-1>=49)
	            {
	                string ans1(1, (char)(i+2)), ans2(1, (char)(j-1));
	                string ans=ans1+ans2;
	                blocks[node].push_back(ans);
	            }
	        }
	        if(i-2>=97)
	        {
	            if(j+1<=56)
	            {
	                string ans1(1, (char)(i-2)), ans2(1, (char)(j+1));
	                string ans=ans1+ans2;
	                blocks[node].push_back(ans);
	            }
	            if(j-1>=49)
	            {
	                string ans1(1, (char)(i-2)), ans2(1, (char)(j-1));
	                string ans=ans1+ans2;
	                blocks[node].push_back(ans);
	            }
	        }
	        if(j-2>=49)
	        {
	            if(i+1<=104)
	            {
	                string ans1(1, (char)(i+1)), ans2(1, (char)(j-2));
	                string ans=ans1+ans2;
	                blocks[node].push_back(ans);
	            }
	            if(i-1>=97)
	            {
	                string ans1(1, (char)(i-1)), ans2(1, (char)(j-2));
	                string ans=ans1+ans2;
	                blocks[node].push_back(ans);
	            }
	        }
	        if(j+2<=56)
	        {
	            if(i+1<=104)
	            {
	                string ans1(1, (char)(i+1)), ans2(1, (char)(j+2));
	                string ans=ans1+ans2;
	                blocks[node].push_back(ans);
	            }
	            if(i-1>=97)
	            {
	                string ans1(1, (char)(i-1)), ans2(1, (char)(j+2));
	                string ans=ans1+ans2;
	                blocks[node].push_back(ans);
	            }
	        }
	    }
	}
	for(auto itr=blocks.begin(); itr!=blocks.end(); itr++)
	{
	    //cout<<itr->first<<"\t";
	    string c=itr->first;
	    ll n=blocks[c].size();
	    ll j=to_number(c);
	    for(ll i=0; i<n; i++)
	    {
	        vertices[j].push_back(to_number(blocks[c][i]));
	        //cout<<blocks[c][i]<<" ";
	    }
	    /*cout<<"\n";
	    cout<<j<<"\t";
	    for(ll i=0; i<n; i++)
	    {
	        cout<<vertices[j][i]<<" ";
	    }
	    cout<<"\n\n";*/
	}
	    string source, dest;
	    cout<<"\t \tFor position mappings, refer to 'mappings.png' \n\n";
	    cout<<"Enter the source (Eg: a1): ";
	    cin>>source;
	    cout<<"Enter the destination (Eg: a1): ";
	    cin>>dest;
	    ll s=to_number(source), d=to_number(dest);
	    for(int i=1; i<=64; i++)
	    {
	        visited[i]=false;
	    }
	    if(s!=d)
        {
            ll n=getPath(s, d);
            cout<<"No. of moves: "<<n<<"\n";
        }
        else
        {
            cout<<"No. of moves: 0\n";
        }
	/*int i=97, j=49;
	string ch1(1, (char)i), ch2(1, (char)j);
	string s=ch1+ch2;
	cout<<s<<"\n";*/
	return 0;
}
