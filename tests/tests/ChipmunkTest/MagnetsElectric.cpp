// This Demo was written by Juan Pablo Carbajal. Nov 2008.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "chipmunk.h"
#include "drawSpace.h"
#include "ChipmunkDemo.h"

#define WIDTH 600
#define HEIGHT 400

#define SINGMAX 10 // Maximum number of singularities per body
#define NMAG 10 // Number of magnets
#define NCHG 10 // Number of charged bodies
#define NMIX 10 // Number of charged magnets

#define COU_MKS  8.987551787e9 // Some physical constants
#define MAG_MKS 1e-7

// Prototypes
struct DataforForce;
typedef void (*SingForceFunc)(struct DataforForce* data);

// Structures
// Singularities
typedef struct ActorSingularity{
	// Number of singularities 
	int Nsing; 
	// Value of the singularities 
	cpFloat value[SINGMAX];
	// Type of the singularities 
	char type[SINGMAX][100]; 
	// Global position of the singularities
	cpVect Gpos[SINGMAX];
	// Local position of the singularities
	cpVect position[SINGMAX];
	// Angle of the singularities measured in the body axes
	cpFloat angle[SINGMAX];
	// Angle of the singularities measured from x
	cpFloat Gangle[SINGMAX];
	// Force function
	SingForceFunc force_func[SINGMAX];
	// Force function
	SingForceFunc torque_func[SINGMAX];
}Sing;

// Data for the force functions
typedef struct DataforForce{
	//Everything in global coordinates
	// Position of the source
	cpVect p0;
	// Observed position
	cpVect p;
	// Relative position source-observed
	cpVect relp;
	// distance, disntace^2, ditance ^3
	cpFloat r[3];
	// angle of the source
	cpFloat ang0;
	// angle of the observed singularity
	cpFloat ang;
	// Foce value
	cpVect F;
	// Torque value
	cpFloat T;
}ForceData;

// Global Varibales
static cpSpace *space;


// **** Forces ****** // 
// Calculate the forces between two bodies. all this functions requieres 
// a pointer to an structure with the necessary fields.

// forces between charges
static void
CoulombForce(ForceData* data){
	data->F=cpvmult(cpvnormalize(data->relp),(cpFloat)COU_MKS/data->r[1]);
}

// forces between magnets
static void
MagDipoleForce(ForceData* data){
	static cpFloat phi,alpha,beta,Fr,Fphi;
	
	// Angle of the relative position vector
	phi=cpvtoangle(data->relp);
	alpha=data->ang0;
	beta=data->ang;		

	alpha =phi - alpha;
	beta = phi - beta;
	
	
	// Components in polar coordinates
	Fr=(2.0e0f*cosf(alpha)*cosf(beta) - sinf(alpha)*sinf(beta));
	Fphi=sinf(alpha+beta);
//	printf("%g %g %g %g %g\n",phi,alpha,beta,Fphi);
	
	// Cartesian coordinates
	data->F=cpv(Fr*cosf(phi)-Fphi*sinf(phi),Fr*sinf(phi)+Fphi*cosf(phi));
	data->F=cpvmult(data->F,-3.e0f*(cpFloat)MAG_MKS/(data->r[1]*data->r[1]));
}

static void
MagDipoleTorque(ForceData* data){
	static cpFloat phi,alpha,beta;
	
	phi=cpvtoangle(data->relp);
	alpha=data->ang0;
	beta=data->ang;		
	alpha =phi - alpha;
	beta = phi - beta;

	// Torque. Though we could use a component of F to save some space, 
	// we use another variables for the sake of clarity.
	
	data->T=((cpFloat)MAG_MKS/data->r[2])*(3.0e0f*cosf(alpha)*sinf(beta) + sinf(alpha-beta));
}
// ******* // 

// This function fills the data structure for the force functions
// The structure Sing has the information about the singularity (charge or magnet)
static void
FillForceData(Sing* source,int inds, Sing* obs,int indo, ForceData* data)
{
	// Global Position and orientation of the source singularity
	 data->p0=source->Gpos[inds];
	 data->ang0=source->Gangle[inds]; 
	 
	// Global Position and orientation of the observed singularity
	 data->p=obs->Gpos[indo];
	 data->ang=obs->Gangle[indo];
	
	// Derived magnitudes
	 data->relp=cpvsub(data->p,data->p0); //Relative position
	 data->r[0]=cpvlength(data->relp); // Distance
	 data->r[1]=cpvlengthsq(data->relp); // Square Distance
	 data->r[2]=data->r[0]*data->r[1]; // Cubic distance
	 
     source->force_func[inds](data); // The value of the force
	 data->F= cpvmult(data->F,source->value[inds]*obs->value[indo]);
}

// Calculation of the interaction
static void
LRangeForceApply(cpBody *a, cpBody *b){
	
	Sing* aux = (Sing*)a->data;
	Sing* aux2 = (Sing*)b->data;
	cpVect delta;
	// General data needed to calculate interaction
	static ForceData fdata;
	fdata.F=cpvzero;
	
	// Calculate the forces between the charges of different bodies
	for (int i=0; i<aux->Nsing; i++)
	{
		for (int j=0; j<aux2->Nsing; j++)
		{
			if(!strcmp(aux->type[i],aux2->type[j]))
			{
				//printf("%s %s\n",aux->type[i],aux2->type[j]);
				FillForceData (aux2,j,aux,i,&fdata);
				
				//Force applied to body A
				delta=cpvsub(aux->Gpos[i], a->p);
				cpBodyApplyForce(a,fdata.F, delta);
				
	 			if(aux->torque_func[i] != NULL)
				{
					//Torque on A
					aux->torque_func[i](&fdata);
					a->t += aux->value[i]*aux2->value[j]*fdata.T;
					
				}
			}
		}
	}
}

// function for the integration of the positions
// The following functions are variations to the starndrd integration in Chipmunk
// you can go ack to the standard ones by doing the appropiate changes.
static void
ChargedBodyUpdatePositionVerlet(cpBody *body, cpFloat dt)
{
    // Long range interaction
    cpArray *bodies = space->bodies;
	static cpBody* B;
	Sing* aux=(Sing*)body->data;
	Sing* aux2;

	// General data needed to calculate interaction
	static ForceData fdata;
	fdata.F=cpvzero;
	
	for(int i=0; i< bodies->num; i++)
	{
	  B=(cpBody*)bodies->arr[i];
	  aux2=(Sing*)B->data;
	  
	  if(B != body)
	  {
        // Calculate the forces between the singularities of different bodies
        LRangeForceApply(body, B);
	  }
	}
	
	cpVect dp = cpvmult(cpvadd(body->v, body->v_bias), dt);
	dp = cpvadd(dp,cpvmult(cpvmult(body->f, body->m_inv), 0.5e0f*dt*dt));
	body->p = cpvadd(body->p, dp);

	cpBodySetAngle(body, body->a + (body->w + body->w_bias)*dt 
				   + 0.5f*body->t*body->i_inv*dt*dt);

	// Update position of the singularities
	aux = (Sing*)body->data;
	for (int i=0; i<aux->Nsing; i++)
	{
        aux->Gpos[i]=cpvadd(body->p,cpvrotate(cpv(aux->position[i].x,
										  aux->position[i].y), body->rot));
		aux->Gangle[i]= aux->angle[i] + body->a;
	}
	
            
 	body->v_bias = cpvzero;
	body->w_bias = 0.0f;
}

// function for the integration of the velocities
static void
ChargedBodyUpdateVelocityVerlet(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{
	body->v = cpvadd(body->v, cpvmult(cpvadd(gravity, cpvmult(body->f, body->m_inv)), 0.5e0f*dt));
	body->w = body->w + body->t*body->i_inv*0.5e0f*dt;
	
	body->f = cpvzero;
	body->t = 0.0e0f;
	
	// Long range interaction
    cpArray *bodies = space->bodies;
	static cpBody* B;

	// General data needed to calculate interaction
	static ForceData fdata;
	fdata.F=cpvzero;
	
	for(int i=0; i< bodies->num; i++)
	{
	  B=(cpBody*)bodies->arr[i];
	  
	  if(B != body)
	  {
        // Calculate the forces between the singularities of different bodies
        LRangeForceApply(body, B);
	  }
	}
	body->v = cpvadd(cpvmult(body->v,damping), cpvmult(cpvadd(gravity, cpvmult(body->f, body->m_inv)), 0.5e0f*dt));
	body->w = body->w*damping + body->t*body->i_inv*0.5e0f*dt;
}

static void 
update(int ticks)
{
	int steps = 10;
	cpFloat dt = 1.0f/60.0f/(cpFloat)steps;
	
	cpArray *bodies = space->bodies;

	for(int i=0; i< bodies->num; i++)
		  cpBodyResetForces((cpBody*)bodies->arr[i]);
	
	for(int i=0; i<steps; i++){
		cpSpaceStep(space, dt);
	}
	
}

static void
make_mag(cpVect p, cpFloat ang, cpFloat mag)
{
	int nverts=6;
	cpVect verts[] = {
		cpv(-10,-10),
		cpv(-10, 10),
		cpv( 10, 10),
		cpv( 15, 5),
		cpv( 15, -5),
		cpv( 10,-10)
	};

	cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, nverts, verts, cpvzero));
	body->p = p;
	body->v = cpvzero;
	cpBodySetAngle(body, ang);
	body->w = 0.0e0f;
	
    // Load the singularities
    Sing *magnet=(Sing*)cpmalloc(sizeof(Sing));
	magnet->Nsing=1; 
	magnet->value[0]=mag;
	sprintf(magnet->type[0],"magdipole"); 

	// The position and angle could be different form the one of the body
	magnet->position[0]=cpvzero;
	magnet->Gpos[0]=cpvadd(p,magnet->position[0]);
	magnet->angle[0]=0.0f;
	magnet->Gangle[0]=ang;
	
	magnet->force_func[0]=MagDipoleForce;
	magnet->torque_func[0]=MagDipoleTorque;

	body->data=magnet;
	
    body->position_func=ChargedBodyUpdatePositionVerlet;
    body->velocity_func=ChargedBodyUpdateVelocityVerlet;
	cpSpaceAddBody(space, body);
	
	cpShape *shape = cpPolyShapeNew(body, nverts, verts, cpvzero);
	shape->e = 0.0f; shape->u = 0.7f;
	cpSpaceAddShape(space, shape);
}

static void
make_charged(cpVect p, cpFloat chg)
{
	int nverts=4;
	cpVect verts[] = {
		cpv(-10,-10),
		cpv(-10, 10),
		cpv( 10, 10),
		cpv( 10,-10)
	};

	cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, nverts, verts, cpvzero));
	body->p = p;
	body->v = cpvzero;
	cpBodySetAngle(body, 0);
	body->w = 0.0e0f;
	
    // Load the singularities
    Sing *charge=(Sing*)cpmalloc(sizeof(Sing));;
	charge->Nsing=1; 
	charge->value[0]=chg;
	sprintf(charge->type[0],"electrical"); 

	// The position and angle could be different form the one of the body
	charge->position[0]=cpvzero;
	charge->Gpos[0]=cpvadd(p,charge->position[0]);
	charge->Gangle[0]=0;
	
	charge->force_func[0]=CoulombForce;
	charge->torque_func[0]=NULL;
	
	body->data=charge;
	
    body->position_func=ChargedBodyUpdatePositionVerlet;
    body->velocity_func=ChargedBodyUpdateVelocityVerlet;
	cpSpaceAddBody(space, body);
	
	cpShape *shape = cpPolyShapeNew(body, nverts, verts, cpvzero);
	shape->e = 0.0f; shape->u = 0.7f;
	cpSpaceAddShape(space, shape);
}
void 
make_mix(cpVect p, cpFloat ang, cpFloat mag,cpFloat chg)
{
	int nverts=5;
	cpVect verts[] = {
		cpv(-10,-10),
		cpv(-10, 10),
		cpv( 10, 10),
		cpv( 20, 0),		
		cpv( 10,-10)
	};

	cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, nverts, verts, cpvzero));
	body->p = p;
	body->v = cpvzero;
	cpBodySetAngle(body, ang);
	body->w = 0.0e0f;
	
    // Load the singularities
    Sing *mix=(Sing*)cpmalloc(sizeof(Sing));;
	mix->Nsing=2; 
	mix->value[0]=mag;
	mix->value[1]=chg;
	sprintf(mix->type[0],"magdipole");
	sprintf(mix->type[1],"electrical");  

	// The position and angle could be different form the one of the body
	mix->position[0]=cpvzero;
	mix->Gpos[0]=cpvadd(p,mix->position[0]);
	mix->position[1]=cpvzero;
	mix->Gpos[1]=cpvadd(p,mix->position[1]);
	mix->Gangle[0]=ang;
	mix->Gangle[1]=ang;	
	
	mix->force_func[0]=MagDipoleForce;
	mix->force_func[1]=CoulombForce;
	mix->torque_func[0]=MagDipoleTorque;
	mix->torque_func[1]=NULL;	
	
	body->data=mix;
	
    body->position_func=ChargedBodyUpdatePositionVerlet;
    body->velocity_func=ChargedBodyUpdateVelocityVerlet;
	cpSpaceAddBody(space, body);
	
	cpShape *shape = cpPolyShapeNew(body, nverts, verts, cpvzero);
	shape->e = 0.0f; shape->u = 0.7f;
	cpSpaceAddShape(space, shape);
}


static cpSpace* 
init(void)
{
	cpResetShapeIdCounter();
	space = cpSpaceNew();
	space->iterations = 5;
	space->gravity = cpvzero; //cpv(0,-100);
	
	cpSpaceResizeActiveHash(space, 30.0f, 2999);

	// Screen border
/*	shape = cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(-320,240), 0.0f);
	shape->e = 1.0; shape->u = 1.0;
	cpSpaceAddShape(space, shape);

	shape = cpSegmentShapeNew(staticBody, cpv(320,-240), cpv(320,240), 0.0f);
	shape->e = 1.0; shape->u = 1.0;
	cpSpaceAddShape(space, shape);

	shape = cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(320,-240), 0.0f);
	shape->e = 1.0; shape->u = 1.0;
	cpSpaceAddShape(space, shape);

	// Reference line
	// Does not collide with other objects, we just want to draw it.
	shape = cpSegmentShapeNew(staticBody, cpv(-320,0), cpv(320,0), 0.0f);
	shape->collision_type = 1;
	cpSpaceAddShape(space, shape);
	// Add a collision pair function to filter collisions
	cpSpaceAddCollisionPairFunc(space, 0, 1, NULL, NULL);
*/		
	
	srand((unsigned int) time(NULL));
    cpVect p;
	cpFloat ang;
	
	// Create magnets
	for(int i=0; i<NMAG; i++)
	{
	  p.x=(2.0e0f*rand()/((cpFloat)RAND_MAX) - 1.0e0f)*WIDTH/2.0f;
  	  p.y=(2.0e0f*rand()/((cpFloat)RAND_MAX) - 1.0e0f)*HEIGHT/2.0f;
  	  ang=(2.0e0f*rand()/((cpFloat)RAND_MAX) - 1.0e0f)*3.1415f;
	  make_mag(p, ang,1.0e7f);
	}
	
	// Create charged objects
	for(int i=0; i<NCHG; i++)
	{
	  p.x=(2.0e0f*rand()/((cpFloat)RAND_MAX) - 1.0e0f)*WIDTH/2.0f;
  	  p.y=(2.0e0f*rand()/((cpFloat)RAND_MAX) - 1.0e0f)*HEIGHT/2.0f;
  	  ang=(2.0e0f*rand()/((cpFloat)RAND_MAX) - 1.0e0f)*3.1415f;
	  make_charged(p, (float)(1.0e-3) *powf(-1.0f,i%2));
	}
		
	// Create charged magnets objects
	for(int i=0; i<NMIX; i++)
	{
      p.x=(2.0e0f*rand()/((cpFloat)RAND_MAX) - 1.0e0f)*WIDTH/2.0f;
  	  p.y=(2.0e0f*rand()/((cpFloat)RAND_MAX) - 1.0e0f)*HEIGHT/2.0f;
  	  ang=(2.0e0f*rand()/((cpFloat)RAND_MAX) - 1.0e0f)*3.1415f;
	  make_mix(p, ang,1.0e7f*powf(-1.0f,i%2), (float)(1.0e-3) *powf(-1.0f,i%2));
	}
	
	return space;
}

static void
destroy(void)
{
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
}

chipmunkDemo MagnetsElectric = {
	"Magnets and Electric Charges (By: Juan Pablo Carbajal)",
	NULL,
	init,
	update,
	destroy,
};
