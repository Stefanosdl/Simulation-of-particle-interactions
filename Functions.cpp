#include <iostream>
#include "Classes.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

extern int bosons,fermions;
int bosons = 0;
int fermions = 0;
extern int newc[7];
int newc[7] = { 0, 0, 0, 0, 0, 0, 0 };		//we keep the final number of every particle

void Electron::InteractWithElectron(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos){
	//at first we call the destructor of the particles that will interact
	particles[pos]->~Particle();
	particles[pos+1]->~Particle();
	delete particles[pos];
	delete particles[pos+1];
	//we initialize the iterator to point at the first particle
	it = particles.begin()+pos;
	//erase this particle and then keep the iterator at this position
	it = particles.erase(it--);
	//insert the new particle and now move the iterator to the next particle
	particles.insert(it++,new Neutron);
	//erase the next particle
	it = particles.erase(it--);
	//and now insert the new particle
	particles.insert(it,new Neutrino);

	newc[0]--;							//1 proton will interact with 1 electron
	newc[2]--;
	newc[1]++;							//1 Neutron created and 1 Neutrino
	newc[4]++;
}

void Proton::InteractElectronWithProton(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
	particles[pos]->~Particle();
	particles[pos+1]->~Particle();
	delete particles[pos];
	delete particles[pos+1];

	it = particles.begin()+pos;
	it = particles.erase(it--);
	particles.insert(it++,new Neutron);
	it = particles.erase(it--);
	particles.insert(it,new Neutrino);

	newc[0]--;
	newc[2]--;
	newc[1]++;
	newc[4]++;
}


void Neutrino::InteractWithNeutrino(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
	particles[pos]->~Particle();
	particles[pos+1]->~Particle();
	delete particles[pos];
	delete particles[pos+1];

	it = particles.begin()+pos;
	it = particles.erase(it--);
	particles.insert(it++,new Proton);
	it = particles.erase(it--);
	particles.insert(it,new Electron);

	newc[1]--;
	newc[4]--;
	newc[0]++;
	newc[2]++;
}

void Neutron::InteractNeutrinoWithNeutron(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
	particles[pos]->~Particle();
	particles[pos+1]->~Particle();
	delete particles[pos];
	delete particles[pos+1];

	it = particles.begin()+pos;
	it = particles.erase(it--);
	particles.insert(it++,new Proton);
	it = particles.erase(it--);
	particles.insert(it,new Electron);

	newc[1]--;
	newc[4]--;
	newc[0]++;
	newc[2]++;
}

void Antineutrino::InteractWithAntineutrino(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
	particles[pos]->~Particle();
	particles[pos+1]->~Particle();
	delete particles[pos];
	delete particles[pos+1];

	it = particles.begin()+pos;
	it = particles.erase(it--);
	particles.insert(it++,new Neutron);
	it = particles.erase(it--);
	particles.insert(it,new Positron);

	newc[5]--;
	newc[0]--;
	newc[1]++;
	newc[3]++;
}

void Proton::InteractAntineutrinoWithProton(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
	particles[pos]->~Particle();
	particles[pos+1]->~Particle();
	delete particles[pos];
	delete particles[pos+1];

	it = particles.begin()+pos;
	it = particles.erase(it--);
	particles.insert(it++,new Neutron);
	it = particles.erase(it--);
	particles.insert(it,new Positron);

	newc[5]--;
	newc[0]--;
	newc[1]++;
	newc[3]++;
}

void Photon::InteractWithPhoton(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
	particles[pos]->~Particle();
	particles[pos+1]->~Particle();
	delete particles[pos];
	delete particles[pos+1];

	it = particles.begin()+pos;
	it = particles.erase(it--);
	particles.insert(it++,new Electron);
	it = particles.erase(it--);
	particles.insert(it,new Positron);

	bosons-=2;
	fermions+=2;
	newc[6]-=2;
	newc[2]++;
	newc[3]++;
}

void Positron::InteractWithPositron(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
	particles[pos]->~Particle();
	particles[pos+1]->~Particle();
	delete particles[pos];
	delete particles[pos+1];

	it = particles.begin()+pos;
	it = particles.erase(it--);
	particles.insert(it++,new Photon);
	it = particles.erase(it--);
	particles.insert(it,new Photon);

	bosons+=2;
	fermions-=2;
	newc[2]--;
	newc[3]--;
	newc[6]+=2;
}
void Electron::InteractPositronWithElectron(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
	particles[pos]->~Particle();
	particles[pos+1]->~Particle();
	delete particles[pos];
	delete particles[pos+1];

	it = particles.begin()+pos;
	it = particles.erase(it--);
	particles.insert(it++,new Photon);
	it = particles.erase(it--);
	particles.insert(it,new Photon);

	bosons+=2;
	fermions-=2;
	newc[2]--;
	newc[3]--;
	newc[6]+=2;
}

void Neutron::NeutronDecay(vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
	particles[pos]->~Particle();
	delete particles[pos];

	it = particles.begin() + pos;
	it = particles.erase(it--);
	particles.insert(it,new Proton);
	//particles.insert(it,new Electron);
	//particles.insert(it,new Antineutrino);
	particles.push_back(new Electron);
	particles.push_back(new Antineutrino);

	fermions+=2;
	newc[1]--;
	newc[0]++;
	newc[2]++;
	newc[5]++;
}

void Proton::ProtonDecay(vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
	particles[pos]->~Particle();
	delete particles[pos];

	it = particles.begin() + pos;
	it = particles.erase(it--);
	particles.insert(it,new Neutron);
	//particles.insert(it,new Positron);
	//particles.insert(it,new Neutrino);
	particles.push_back(new Positron);
	particles.push_back(new Neutrino);

	fermions+=2;
	newc[0]--;
	newc[1]++;
	newc[3]++;
	newc[4]++;
}






void PrintValues(int c[],int ec) {
	cout<<endl<<"Number of Protons created : "<<c[0]<<endl
	<<"Number of Neutrons created : "<<c[1]<<endl
	<<"Number of Electrons created : "<<c[2]<<endl
	<<"Number of Positrons created : "<<c[3]<<endl
	<<"Number of Neutrinos created : "<<c[4]<<endl
	<<"Number of Antineutrinos created : "<<c[5]<<endl
	<<"Number of Photons created : "<<c[6]<<endl
	<<"Total electric charge is : "<<ec<<endl<<endl;
}

void PrintNew(int newc[],int c[],int fermions,int bosons,int ec,int new_ec,double totalmass,double new_mass,double spin,double new_spin) {
	cout<<endl<<"The new number of particles is : "<<endl
		<<"Number of Protons : "<<newc[0]<<endl
		<<"Number of Neutrons : "<<newc[1]<<endl
		<<"Number of Electrons : "<<newc[2]<<endl
		<<"Number of Positrons : "<<newc[3]<<endl
		<<"Number of Neutrinos : "<<newc[4]<<endl
		<<"Number of Antineutrinos : "<<newc[5]<<endl
		<<"Number of Photons : "<<newc[6]<<endl
		<<endl<<"The percentage change in the number of every particle is : "<<endl
		<<"Percentage change of Protons : "<<(double)(newc[0]-c[0])*100/c[0]<<"%"<<endl
		<<"Percentage change of Neutrons : "<<(double)(newc[1]-c[1])*100/c[1]<<"%"<<endl
		<<"Percentage change of Electrons : "<<(double)(newc[2]-c[2])*100/c[2]<<"%"<<endl
		<<"Percentage change of Positrons : "<<(double)(newc[3]-c[3])*100/c[3]<<"%"<<endl
		<<"Percentage change of Neutrinos : "<<(double)(newc[4]-c[4])*100/c[4]<<"%"<<endl
		<<"Percentage change of Antineutrinos : "<<(double)(newc[5]-c[5])*100/c[5]<<"%"<<endl
		<<"Percentage change of Photons : "<<(double)(newc[6]-c[6])*100/c[6]<<"%"<<endl;
		if(fermions>bosons){
			cout<<"Living in a material world!"<<endl;
		}
		else if(bosons>fermions){
			cout<<"Radiation prevails!"<<endl;
		}
		else{
			cout<<"Equilibrium?"<<endl;
		}
		if(new_ec == ec) {
			cout<<"Conservation verified"<<endl;
		}
		cout<<"The difference in the mass is : "<<new_mass-totalmass<<" MeV/c^2"<<endl
			<<"The difference in the spin is : "<<new_spin-spin<<endl;
		if(new_mass-totalmass == 0 || new_spin-spin == 0){
			cout<<"How it comes!"<<endl;
		}
	cout<<endl;
}
