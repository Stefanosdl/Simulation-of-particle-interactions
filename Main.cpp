#include <iostream>
#include "Classes.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

extern int bosons,fermions;
extern int newc[7];
extern double new_mass,new_spin;


void PrintValues(int [],int );
void PrintNew(int [],int [],int ,int ,int ,int ,double ,double ,double ,double );

int main(int argc,char *argv[]) {
	srand(time(NULL));
	int c[7] = { 0, 0, 0, 0, 0, 0, 0 };		//we keep the initial  number of every particle
	int ec = 0;
	int new_ec = 0;
	int randparticle = 0;
	int type = 0;
	int vectorsize = 0;
	double mass = 0;
	double spin = 0;
	double new_mass = 0;
	double new_spin = 0;

	vector <Particle *> particles;
	vector <Particle *>::iterator it;
	it = particles.begin();
	srand(time(NULL));
	for(int i=0; i<atoi (argv[1]); i++){
		type = rand()%7 + 1;
		//randomly generate the type of the particle
		switch (type) {
			case 1 :
				particles.push_back(new Proton);
				c[0]++;							//the initial number of protons
				newc[0]++;						//the new number of protons
				fermions++;						//number of fermions created
				ec += particles.at(i)->get_electric_charge();
				mass += particles.at(i)->get_mass();
				spin += particles.at(i)->get_spin();
				break;
			case 2 :
				particles.push_back(new Neutron);
				ec += particles.at(i)->get_electric_charge();
				mass += particles.at(i)->get_mass();
				spin += particles.at(i)->get_spin();
				fermions++;
				c[1]++;
				newc[1]++;
				break;
			case 3 :
				particles.push_back(new Electron);
				ec += particles.at(i)->get_electric_charge();
				mass += particles.at(i)->get_mass();
				spin += particles.at(i)->get_spin();
				fermions++;
				c[2]++;
				newc[2]++;
				break;
			case 4 :
				particles.push_back(new Positron);
				ec += particles.at(i)->get_electric_charge();
				mass += particles.at(i)->get_mass();
				spin += particles.at(i)->get_spin();
				fermions++;
				c[3]++;
				newc[3]++;
				break;
			case 5 :
				particles.push_back(new Neutrino);
				ec += particles.at(i)->get_electric_charge();
				mass += particles.at(i)->get_mass();
				spin += particles.at(i)->get_spin();
				fermions++;
				c[4]++;
				newc[4]++;
				break;
			case 6 :
				particles.push_back(new Antineutrino);
				ec += particles.at(i)->get_electric_charge();
				mass += particles.at(i)->get_mass();
				spin += particles.at(i)->get_spin();
				fermions++;
				c[5]++;
				newc[5]++;
				break;
			case 7 :
				particles.push_back(new Photon);
				ec += particles.at(i)->get_electric_charge();
				mass += particles.at(i)->get_mass();
				spin += particles.at(i)->get_spin();
				bosons++;
				c[6]++;
				newc[6]++;
				 break;
		}
	}

	//function to print the initial ,asked, values
	PrintValues(c,ec);

	for (int i=0 ; i<atoi (argv[2]); i++){
		randparticle = rand()%particles.size();
		vectorsize = particles.size() - 1;
		//first check if there is another particle on the right side
		if(randparticle<vectorsize){
			//check for interaction with the right particle
			if(!particles[randparticle]->Interact(particles[randparticle+1],particles,it,randparticle)) continue;
		}
		//if there was no interaction go on
		//now check if there is a particle at the left side
		if(randparticle>0){
			//check for interaction with the left particle
			if(!particles[randparticle-1]->Interact(particles[randparticle],particles,it,randparticle-1)) continue;
		}
		//no interaction on both sides
		//it is time for the decay
		particles[randparticle]->Decay(particles,it,randparticle);
	}
	//lets get the new mass and spin
	for(int unsigned i=0; i<particles.size(); i++){
		new_mass += particles.at(i)->get_mass();
		new_spin += particles.at(i)->get_spin();
		new_ec  += particles.at(i)->get_electric_charge();
	}

	//function to print new mass,new spin etc.
	PrintNew(newc,c,fermions,bosons,ec,new_ec,mass,new_mass,spin,new_spin);

	//and now delete the vector
	for( it=particles.begin(); it!=particles.end(); ++it){
		delete (*it);
	}
	particles.clear();

	return 0;
}
