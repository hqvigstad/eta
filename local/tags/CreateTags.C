//_________________________________________________________________________
// Macro to create the tag files from:
// i)  AliESDs that are stored locally.
// ii) AliESDs that are stored in the CAF.
// iii)AliESDs that are stored in alien.
// The tag files are stored according to the value set in the SetStorage method
// Use Case : 
//          SetStorage(0) --> store the tags locally
//          SetStorage(1) --> store the tags in the grid
//          else the program will abort!!!                                    
//                                             
// As a final step the user can create a single merged tag file.         
//_________________________________________________________________________
void CreateTags() {
  //___________________________________//
  //create an AliTagCreator object
  AliESDTagCreator *tagc = new AliESDTagCreator(); 
    
  //___________________________________//
  //_____ Storage of the tag files:____//
  //________0-->local, 1-->alien_______//
  //___________________________________//
  tagc->SetStorage(0);
  //Define the grid's path where the tag files will be stored
  //tagc->SetGridPath("Tags/output");
  //Define the SE where the tag files will be stored
  //tagc->SetSE("ALICE::CERN::se01");

  //___________________________________//
  //________Locally stored ESDs________//
  //___________________________________//
  //create the tag files for the locally stored ESDs
  //tagc->ReadLocalCollection("/afs/cern.ch/user/a/agheata/public/GridTutorial/PDC08");
  tagc->ReadLocalCollection("/home/hq/work/sim/LHC11d2/119161");

  //___________________________________//
  //___________Merge the tags__________//
  //___________________________________//
  //Merge the tags and store the merged file
  tagc->MergeTags("ESD");
}

