#include "tests.h"

void testVictim()
{
	cout << "Testing victim" << endl;
	Victim v{ "name1","origin",10,"ph.png" };
	assert(v.getName() == "name1");
	assert(v.getPlaceOfOrigin() == "origin");
	assert(v.getPhoto() == "ph.png");
	assert(v.getAge() == 10);
	assert(v.toString().size() > 0);
	assert(v.getHTMLString().size() > 0);
	Victim v2("name1", "", 0, "");
	Victim v3("name2", "", 0, "");
	assert(v == v2);
	assert(v != v3);
	ofstream fout("tests/testVictims.txt");
	fout << v;
	fout << v3;
	fout.close();
	ifstream fin("tests/testVictims.txt");
	Victim v4;
	fin >> v4;
	assert(v == v4);
	fin >> v4;
	assert(v3 == v4);
	fin.close();
	remove("tests/testVictims.txt");
}

void testRepository()
{
	cout << "Testing repository" << endl;
	Repository repo;
	Victim v0;

	try { repo.addVictim(v0); assert(false); }
	catch (exception&) { assert(true); }

	try { repo.setVictimsFile("c:/xd1/xdF"); assert(false); }
	catch (exception&) {assert(true);}
	repo.setVictimsFile("tests/testRepo.txt");
	repo.setVictimsFile("tests/testRepo.txt");
	
	
	Victim v1{ "name1","origin",10,"ph.png" };
	Victim v2{ "name2","origin",10,"ph.png" };

	repo.addVictim(v1);
	assert(repo.getVictim("name1") == v1);
	assert(repo.getVictims().size() == 1);
	assert(repo.getVictims()[0] == v1);
	try { repo.getVictim(""); assert(false); }
	catch (exception&) { assert(true); }
	repo.addVictim(v2);
	try {repo.addVictim(v2); assert(false);}
	catch (exception&) {assert(true);}

	assert(repo.getVictims().size() == 2);
	Victim v3{ "name2","newOrigin",20,"ph2.png" };
	repo.updateVictim(v3);
	
	try { repo.updateVictim(v0); assert(false); }
	catch (exception&) { assert(true); }

	assert(repo.getVictims()[1].getAge() == 20);
	repo.deleteVictim(v1);
	try { repo.deleteVictim(v0); assert(false); }
	catch (exception&) { assert(true); }

	assert(repo.getVictims().size() == 1);
	assert(repo.getVictims()[0].getName() == "name2");
	Victim v4 = repo.getNextVictim();
	assert(v4.getName() == "name2");
	assert(repo.getNextVictim().getName() == v4.getName());

	AssistantRepository ar("tests/testRepo2.txt");
	assert(ar.getVictims().size() == 0);

	ar.addVictim(v4);
	repo.deleteVictim(v4);
	assert(ar.getVictims().size() == 1);
	assert(ar.getVictims()[0].getName() == "name2");
	try { repo.getNextVictim(); assert(false); }
	catch (exception&) { assert(true); }
	remove("tests/testRepo2.txt");
	remove("tests/testRepo.txt");
}


void testService()
{
	cout << "Testing controller" << endl;
	Repository repo{};
	Service srv{ repo };
	srv.createMylistRepo("tests/testRepo2.txt","txt");
	srv.setFile("tests/testRepo.txt");
	srv.addVictimToRepo("name1", "origin", 10, "ph.png");
	try {srv.addVictimToRepo("name1", "origin", 10, "ph.png"); assert(false);}
	catch (exception&) { assert(true); }
	assert(srv.getAllVictims()[0].getName() == "name1");
	srv.addVictimToRepo("name2", "origin2", 20, "ph2.png");
	assert(srv.getAllVictims().size() == 2);

	srv.updateVictim("name2", "o22", 33, "p22.jgp");
	try {srv.updateVictim("badName", "o22", 33, "p22.jgp"); assert(false);}
	catch (exception&) { assert(true); }
	assert(srv.getAllVictims()[1].getAge() == 33);

	try {srv.deleteVictim("badName"); assert(false);}
	catch (exception&) { assert(true); }
	srv.deleteVictim("name1");
	assert(srv.getAllVictims().size() == 1);
	assert(srv.getAllVictims()[0].getName() == "name2");
	

	assert(srv.filterVictims("", 22).size() == 0);
	assert(srv.filterVictims("o22", 44).size() == 1);
	srv.nextVictim();
	assert(srv.getCurrentVictim().getName() == "name2");
	try {srv.moveVictimToAssistantList("badname"); assert(false);}
	catch (exception&) { assert(true); }
	srv.moveVictimToAssistantList("name2");
	assert(srv.getAllVictims().size() == 0);

	srv.addEntries();
	srv.addEntries();
	assert(srv.getAllVictims().size() == 10);
	remove("tests/testRepo2.txt");
	remove("tests/testRepo.txt");
}

/*
void testDynamicVector()
{
	DynamicVector<int> a;
	a.add(1);
	a.add(2);
	assert(a.getSize() == 2);
	assert(a[0] == 1);
	a[1] = 999;
	assert(a[1] == 999);
	DynamicVector<int> b;
	a = a;
	b = a;
	a.deletePosition(0);
	assert(a[0] == 999);
	assert(b.getSize() == 2);
	assert(b[0] == 1);

	// test iterator
	DynamicVector<int>::Iterator it = b.begin();
	assert(*it == 1);
	assert(it != b.end());
	++it;
	assert(*it == 999);
	b.add(30);
	it++;
	assert(*it == 30);
	++it;
}*/

void testAll()
{
	testVictim();
	testRepository();
	testService();
	_CrtDumpMemoryLeaks();
	cout << "All tests passed" << endl<<endl;
	system("timeout 3");
	system("cls");
}
