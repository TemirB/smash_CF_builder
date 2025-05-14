/**
 * \class StHbtBasicEventCut
 * \brief The basic cut for events
 *
 * Cuts on event multiplicity, z-vertex position, trigger and other event variables
 */

#ifndef StHbtBasicEventCut_h
#define StHbtBasicEventCut_h

// C++ headers
#include <vector>

// StHbtMaker headers
// Base
#include "StHbtMaker/StHbtBaseEventCut.h"
// Infrastructure
#include "StHbtMaker/StHbtEvent.h"
#include "StHbtMaker/StHbtString.h"

// ROOT headers
#include "TList.h"
#include "TString.h"

//_________________
class StHbtBasicEventCut : public StHbtBaseEventCut {

 public:
  /// Constructor
  StHbtBasicEventCut();
  /// Copy contructor
  StHbtBasicEventCut(const StHbtBasicEventCut& c);
  /// Assignment operator
  StHbtBasicEventCut& operator=(const StHbtBasicEventCut& c);
  /// Destructor
  virtual ~StHbtBasicEventCut();

  /// Check bad run flag
  void setCheckBadRun(bool check) { mCheckBadRun = check; }
  /// Set min and max acceptable event multiplicity
  void setEventMult(const int& lo, const int& hi);
  /// Set min and max acceptable vertex z-coordinate
  void setVertZPos(const float& lo, const float& hi) { mVertZPos[0] = lo; mVertZPos[1] = hi; }
  /// Set min and max acceptable (Vz-VpdVz) values
  void setVpdVzDiff(const float& lo, const float& hi){ mVpdVzDiff[0] = lo; mVpdVzDiff[1] = hi; }
  /// Set x shift of primary vertex, min and max acceptrable
  /// radial position of the vertex
  void setVertXShift(const float& shift)             { mVertXShift = shift; }
  /// Set y shift of primary vertex, min and max acceptrable
  /// radial position of the vertex
  void setVertYShift(const float& shift)             { mVertYShift = shift; }
  /// Set min and max acceptable radial position of primary vertex
  void setVertRPos(const float& lo, const float& hi) { mVertRPos[0] = lo; mVertRPos[1] = hi; }
  /// Set min and max acceptable values of sphericity
  void setSphericity(const float& lo, const float& hi) { mSphericity[0] = lo; mSphericity[1] = hi; }
  /// Set min and max acceptable TOF tray multiplicity
  void setBTofTrayMult(const int& lo, const int& hi);
  /// Set min and max acceptable TOF-matched tracks
  void setBTofMatchMult(const int& lo, const int& hi);
  /// Number of events passed
  int nEventsPassed() const                          { return mNEventsPassed; }
  /// Number of events failed
  int nEventsFailed() const                          { return mNEventsFailed; }
  /// Add trigger to select
  void addTriggerId(const unsigned int& id);
  /// Add trigger to select
  void setTriggerId(const unsigned int& id)          { addTriggerId( id ); }
  /// Set the min and max allowed event plane angle
  void setEventPlaneAngle(const float& lo, const float& hi)  { mPsiEP[0] = lo; mPsiEP[1] = hi; }
  /// Set the min and max allowed event plane angle
  void setEPAngle(const float& lo, const float& hi)  { setEventPlaneAngle( lo, hi ); }
  /// Set impact parameter to select
  void setImpactParameter(const float& lo, const float& hi) { mImpactPar[0] = lo; mImpactPar[1]=hi; }

  /// Set centrality bins to select (out of 9)
  void setCent9(const int& lo, const int& hi);

  virtual TList* appendSettings(TList*, const TString& prefix="") const;
  // Construct report
  virtual StHbtString report();
  /// Event cut
  virtual bool pass(const StHbtEvent* event);
  /// Clone event cut
  virtual StHbtBasicEventCut* clone() const
  { StHbtBasicEventCut* c = new StHbtBasicEventCut(*this); return c; }
  
  /// Print cut information
  void setVerbose(const bool& verbose) { mVerbose = verbose; }

 private:

  /// Check bad run flag. By default it is true (see constructor for more info)
  bool mCheckBadRun;
  /// Range of multiplicity
  short mRefMult[2];
  /// Range of z-position of vertex
  float mVertZPos[2];
  /// Range of (Vz - VpdVz) of vertex
  float mVpdVzDiff[2];
  /// Shift of the primary vertex in x direction
  float mVertXShift;
  /// Shift of the primary vertex in y direction
  float mVertYShift;
  /// Min/max values of the primary vertex radial position
  float mVertRPos[2];
  /// Range of min and max values of event sphericity
  float mSphericity[2];
  /// Range of TOF tray multiplicity
  short mBTofTrayMult[2];
  /// Range of TOF matched tracks (multplicity)
  short mBTofMatch[2];
  // Range of centralities
  short mCent9[2];
  /// Range of vzero ep angle
  float mPsiEP[2];
  /// Number of events checked by this cut that passed
  unsigned int mNEventsPassed;
  /// Number of events checked by this cut that failed
  unsigned int mNEventsFailed;
  /// If set, only given trigger will be selected
  std::vector<unsigned int> mTriggersToSelect;
  /// Impact parameter (for simulation studies only)
  float mImpactPar[2];

  /// Print cut information
  bool mVerbose;

  /// Method that looks at the bad run lists
  bool isInBadRunList(int runNumber);

  /// Bad run list for Au+Au at 7 GeV/n (BES-I)
  static const std::vector<unsigned int> bad_run_list_7gev;
  /// Bad run list for Au+Au at 11 GeV/n (BES-I)
  static const std::vector<unsigned int> bad_run_list_11gev;
  /// Bad run list for Au+Au at 14 GeV/n (BES-I)
  static const std::vector<unsigned int> bad_run_list_14gev;
  /// Bad run list for Au+Au at 19 GeV/n (BES-I)
  static const std::vector<unsigned int> bad_run_list_19gev;
  /// Bad run list for Au+Au at 27 GeV/n (BES-I)
  static const std::vector<unsigned int> bad_run_list_27gev;
  /// Bad run list for Au+Au at 39 GeV/n (BES-I)
  static const std::vector<unsigned int> bad_run_list_39gev;
  /// Bad run list for Au+Au at 62 GeV/n (BES-I)
  static const std::vector<unsigned int> bad_run_list_62gev;
  /// Bad run list for Au+Au at 200 GeV/n (BES-I)
  static const std::vector<unsigned int> bad_run_list_200gev;
  /// Bad run list for d+Au at 200 GeV/n (Run16)
  static const std::vector<unsigned int> bad_run_list_dau200_2016;
  /// Bad run list for 3He+Au at 200 GeV/n (Run14)
  static const std::vector<unsigned int> bad_run_list_he3au200_2014;

#ifdef __ROOT__
  ClassDef(StHbtBasicEventCut, 4);
#endif
};

#endif // StHbtBasicEventCut_h
