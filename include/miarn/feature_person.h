/**
@par Configuration file options

- inc_fid_index (integer)
- default: 0
- incoming Feature index
- leg_clean_ticks (integer)
- default: 1
- ticks needed to remove legs
- person_clean_ticks (integer)
- default: 10
- ticks needed to remove persons
- leg_update_radius (float)
- default: 0.6
- radius to search for the same leg in mm
- person_radius (float)
- default: 0.6
- radius to search for the same person in mm

Joao Xavier smogzer_at_gmail.com
*/

#include <list>
#include <cmath>
#include "miarn/xy.h"
#include "miarn/fiducial.h"

//#include <erf/erf_debug.hpp>

enum dynamic_t{still, moving};
struct Person;
struct leg;
bool AttachLeg(Person* a, leg* b);
bool DetachLeg(Person* a, leg* b);

struct Person {
    Person(leg * lleg, leg * rleg);
    Person() {}
    ~Person();

    int seen_counter;
    xy pos[3];
    /// pointers to the person leg
    leg* lleg_ptr, *rleg_ptr;

    void update();
};

struct leg {
    leg() {}
    ~leg();

    //int lbegin, lend;
    //int leg_diameter;
    /// is it moving ?
    dynamic_t dynamics;
    /// last seen in ?
    int seen_counter;
    /// born position
    xy born;
    /// current position
    xy pos[3];
    /// the person that owns the leg
    Person * ptrPerson;
    void update(const xy& new_pos);                 //, const int& lbeg,const int& lend);//, const int& diam
    leg(const xy& new_pos,const xy& xyold);         //,const int& lbeg,const int& lend);//, const int& diam);
};

struct FeatureLegTracker{

    bool UpdateFeatureData();
    void FillFeature();

    void LegMatchInTime();
    void LegClean();
    void LegCreate();
    void PersonUpdate();
    void PersonCreate();
    void LCReset();
    void CreateIncoming();

    float segmentation_threshold;
    float leg_update_radius;
    float person_radius;
    int leg_clean_ticks;
    int person_clean_ticks;

    /// Lists of structures
    std::list<xy> list_candidates;
    std::list<xy> list_incoming;
    std::list<miarn_fiducial_item> list_2legs;
    std::list<leg*> list_legs;
    std::list<Person*> list_persons;

    /// Add the structures to fiducial list
    void AddPerson(float, float, float, float, float, float, float, float, float, float);
    void AddLeg(float pos_x, float pos_y,float past_pos_x, float past_pos_y,float future_pos_x, float future_pos_y);

    miarn_fiducial_data fdata;
	miarn_fiducial_data fdata_out;
};
