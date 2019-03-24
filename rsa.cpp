#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <cmath>
long gcd(long a, long h) 
{ 
  long temp; 
  while (1) 
  { 
    temp = a%h; 
    if (temp == 0) 
      return h; 
    a = h; 
    h = temp; 
  } 
} 

//find number which are relatively prime to number "no1"
long find_co_prime(long no1, long double *no2, long upper_limit)
{
	long rem = no1%2;	
	for( long i =2;i<upper_limit;i++)
	{
		 if(gcd(i,upper_limit)==1)
		 {
			*no2 = i;
			return i;
		 }
	}
	return -1;
}

//	https://stackoverflow.com/a/36398956/5988038
//	modulo ( base, power, divisor)
long double modulo(long long a, long long b, long long n) 
{
  long long x=1, y=a; 
  while (b > 0) 
	{
  	if (b%2 == 1) 
		{
    	x = (x*y) % n; // multiplying with base
    }
    y = (y*y) % n; // squaring the base
    b /= 2;
  }
  return x % n;
}

//key generation
void key_gen (long double prime1, long double prime2, long double *private_key, long double *public_key, long double *nn)
{
	long double n = prime1 * prime2, phi = (prime1-1)*(prime2 -1), e,d;
	long double  e1 = find_co_prime(n,&e,phi);
	long double a = e1,m=phi; 
	for ( d=1.0; d<m; d=d+1.0) 
  {  
		if (std::fmod((a*d), m) == 1) //exits when d is found
   		break; 
	}
	*private_key = d;
	*public_key = e;
	*nn = n;
}

void encryption( long double data, long double *public_key, long double *nn, long double *encrypted_data)
{
	long double c,p=*public_key, intermediate1;
	intermediate1 = std::pow(data,p);
	c= std::fmod((double)intermediate1,(double)(*nn));
	*encrypted_data = c;
}

void decryption (long double encr_data, long double *private_key, long double *nn, long double *data)
{
	long double c;
	c= modulo(encr_data,*private_key,*nn);
	*data = c;
}

int main()
{
	long p,q,data;
	long double priv_key,pubkey,nn,encr_data,decr_data;
	std::cout<<"Enter p & q :";
	std::cin>>p>>q;
	key_gen(p,q,&priv_key,&pubkey,&nn);
	std::cout<<"P="<<p<<"\t Q="<<q<<"\tnn ="<<nn<<"\nprivate key="<<priv_key<<"\npubkey ="<<pubkey<<"\nEnter data:";
	std::cin>>data;
	encryption(data,&pubkey,&nn,&encr_data);
	decryption(encr_data,&priv_key,&nn,&decr_data);
	std::cout<<"\nencrypted data ="<<encr_data<<"\ndecrypted data ="<<decr_data<<std::endl;
	return 0;
}
