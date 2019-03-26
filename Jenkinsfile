//Jenkins files are in shared libaries. Please see: https://github.com/tijcolem/nrel_cbci_jenkins_libs 
 
@Library('cbci_shared_libs') _

// Build for PR only. CHANGE_ID & CHANGE_TARGET will not be set if not a PR
if ((env.CHANGE_ID) && (env.CHANGE_TARGET) ) { // check if set

  openstudio_incremental_build()
    
}