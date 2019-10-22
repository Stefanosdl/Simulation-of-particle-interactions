#include <iostream>
#include <vector>

using namespace std;

class Particle {
protected:
	double mass;
	float spin;
	int electric_charge;
public:
	int get_electric_charge(){ return electric_charge; }
	double get_mass(){ return mass; }
	double get_spin(){ return spin; }
	virtual int Interact(Particle *,vector <Particle *> &,vector <Particle *>::iterator it,int pos) { return 0;	}
	virtual void InteractWithPhoton(Particle *,vector <Particle *> &,vector <Particle *>::iterator it,int pos) {	}
	virtual void InteractWithNeutrino(Particle *,vector <Particle *> &,vector <Particle *>::iterator it,int pos) {	}
	virtual void InteractNeutrinoWithNeutron(Particle *,vector <Particle *> &,vector <Particle *>::iterator it,int pos) {	}
	virtual void InteractWithAntineutrino(Particle *,vector <Particle *> &,vector <Particle *>::iterator it,int pos) {	}
	virtual void InteractAntineutrinoWithProton(Particle *,vector <Particle *> &,vector <Particle *>::iterator it,int pos) {	}
	virtual void InteractWithElectron(Particle *,vector <Particle *> &,vector <Particle *>::iterator it,int pos) { 	}
	virtual void InteractElectronWithProton(Particle *,vector <Particle *> &,vector <Particle *>::iterator it,int pos) {	}
	virtual void InteractWithPositron(Particle *,vector <Particle *> &,vector <Particle *>::iterator it,int pos) {	}
	virtual void InteractPositronWithElectron(Particle *,vector <Particle *> &,vector <Particle *>::iterator it,int pos) {	}
	virtual void Decay(vector <Particle *> &,vector <Particle *>::iterator it,int pos) {	}
	virtual void NeutronDecay(vector <Particle *> &,vector <Particle *>::iterator it,int pos) {	}
	virtual void ProtonDecay(vector <Particle *> &,vector <Particle *>::iterator it,int pos) {	}
	Particle(double mass,float spin,int electric_charge ):
		mass(mass),spin(spin),electric_charge(electric_charge)
	{	}
	virtual ~Particle() {	}
};

class Fermion:public Particle {
protected:
	string statistics;
public:
	Fermion(double mass,float spin,int electric_charge): Particle(mass,spin,electric_charge)
	{
		statistics = "Fermi-Dirac";
	}
	virtual ~Fermion() {	}
};

class Boson:public Particle {
protected:
	string statistics;
public:
	Boson(double mass,float spin,int electric_charge): Particle(mass,spin,electric_charge)
	{
		statistics = "Bose_Einstein";
	}
	virtual ~Boson() {	}
};

class Proton:public Fermion {
public:
	int Interact(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
		particles[pos+1]->InteractWithAntineutrino(particles[pos],particles,it,pos);
		particles[pos+1]->InteractWithElectron(particles[pos],particles,it,pos);
		return 1;
	}
	void InteractElectronWithProton(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos);
	void InteractAntineutrinoWithProton(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos);
	void Decay(vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
		particles[pos]->ProtonDecay(particles,it,pos);
	}
	void ProtonDecay(vector <Particle *> &particles,vector <Particle *>::iterator it,int pos);
	Proton():Fermion(938.27208,0.5,1){
		cout<<"A proton has been constructed"<<endl
			<<"Statistics of : "<<statistics<<endl;
	}
	~Proton() {
		cout<<"A proton will be destroyed"<<endl;
	}
};

class Neutron:public Fermion {
public:
	int Interact(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
		particles[pos+1]->InteractWithNeutrino(particles[pos],particles,it,pos);
		return 1;
	}
	void InteractNeutrinoWithNeutron(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos);
	void Decay(vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
		particles[pos]->NeutronDecay(particles,it,pos);
	}
	void NeutronDecay(vector <Particle *> &particles,vector <Particle *>::iterator it,int pos);
	Neutron():Fermion(939.56541,0.5,0){
		cout<<"A neutron has been constructed"<<endl
			<<"Statistics of : "<<statistics<<endl;
	}
	~Neutron() {
		cout<<"A neutron will be destroyed"<<endl;
	}
};

class Electron:public Fermion {
public:
	int Interact(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
		particles[pos+1]->InteractWithPositron(particles[pos],particles,it,pos);
		return 1;
	}
	void InteractWithElectron(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos);
	void InteractPositronWithElectron(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos);
	Electron():Fermion(0.510998946,0.5,-1){
		cout<<"An electron has been constructed"<<endl
			<<"Statistics of : "<<statistics<<endl;
	}
	~Electron() {
		cout<<"An electron will be destroyed"<<endl;
	}
};

class Positron:public Fermion {
public:
	int Interact(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
		particles[pos+1]->InteractPositronWithElectron(particles[pos],particles,it,pos);
		return 1;
	}
	void InteractWithPositron(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos);
	Positron():Fermion(0.510998946,0.5,1){
		cout<<"A positron has been constructed"<<endl
			<<"Statistics of : "<<statistics<<endl;
	}
	~Positron() {
		cout<<"A positron will be destroyed"<<endl;
	}
};

class Neutrino:public Fermion {
public:
	int Interact(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
		particles[pos+1]->InteractNeutrinoWithNeutron(particles[pos],particles,it,pos);
		return 1;
	}
	void InteractWithNeutrino(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos);
	Neutrino():Fermion(0.000000320,0.5,0){				//The mass in MeV/c^2
		cout<<"A neutrino has been constructed"<<endl
			<<"Statistics of : "<<statistics<<endl;
	}
	~Neutrino() {
		cout<<"A neutrino will be destroyed"<<endl;
	}
};

class Antineutrino:public Fermion {
public:
	int Interact(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
		particles[pos+1]->InteractAntineutrinoWithProton(particles[pos],particles,it,pos);
		return 1;
	}
	void InteractWithAntineutrino(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos);
	Antineutrino():Fermion(0.000000320,0.5,0){			//The mass in MeV/c^2
		cout<<"An antineutrino has been constructed"<<endl
			<<"Statistics of : "<<statistics<<endl;
	}
	~Antineutrino() {
		cout<<"An antineutrino will be destroyed"<<endl;
	}
};

class Photon:public Boson {
public:
	int Interact(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos) {
		particles[pos+1]->InteractWithPhoton(particles[pos],particles,it,pos);
		return 1;
	}
	void InteractWithPhoton(Particle *,vector <Particle *> &particles,vector <Particle *>::iterator it,int pos);
	Photon():Boson(0,1,0){
		cout<<"A photon has been constructed"<<endl
			<<"Statistics of : "<<statistics<<endl;
	}
	~Photon() {
		cout<<"A photon will be destroyed"<<endl;
	}
};
