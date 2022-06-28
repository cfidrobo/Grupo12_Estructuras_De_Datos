#define _CRT_SECURE_NO_WARNINGS 1

#include"HashBucket.h"
#include"hashbucket.cpp"


int main()
{
	HashBucket<string, string, StringFunc> h;
	h.Insert("andres", "789457");
	h.Insert("marco", "010202");
	h.Insert("maria", "015455");
	h.Insert("mauricio", "684155");

	HashBucket<string, string, StringFunc> g(h);
	g.Remove("mauricio");
	h.Print();
	return 0;
}