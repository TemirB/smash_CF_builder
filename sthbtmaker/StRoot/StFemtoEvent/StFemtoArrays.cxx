//
// The class holds FemtoDst names and types
//

// FemtoDst headers
#include "StFemtoArrays.h"

//_________________
StFemtoArrays::StFemtoArrays() {
  /* empty */
}

//_________________
StFemtoArrays::~StFemtoArrays() {
  /* empty */
}

//    ARRAY NAMES
//_________________
const char* StFemtoArrays::femtoArrayNames [NAllFemtoArrays] = { "Event",
								 "Track",
								 "V0",
								 "Xi",
								 "EpdHit",
								 "KFP"
};

//   ARRAY TYPES
//_________________
const char* StFemtoArrays::femtoArrayTypes [NAllFemtoArrays] = { "StFemtoEvent",
								 "StFemtoTrack",
								 "StFemtoV0",
								 "StFemtoXi",
								 "StFemtoEpdHit",
								 "StFemtoKFP"
};

///              ARRAY SIZES
/// These are intial sizes. Automatically resized if too small.
/// Choosing too large initial values gives a performance penalty when reading
/// only selected femtoDst branches
//_________________
int StFemtoArrays::femtoArraySizes[NAllFemtoArrays] = { 1, 500, 1, 1, 500, 50 };
