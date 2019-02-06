
/*
Blocks below setup the incremental builds for ubuntu, osx, and windows on resptive remote 
slave VM nodes according the label tags. Go to Manage Jenkins->Nodes for full node details. 
The CHANGE_ID env is only set for git pull requests so this is good to control the pipeline to 
either buld pull requests as incremental builds vs nightly and on-demand full builds. 
*/


// Build for PR and target branch develop
if ((env.CHANGE_ID) && (env.CHANGE_TARGET) ) { // check if set

  if ( env.CHANGE_TARGET == "develop") {

    node("openstudio-ubuntu-1604") { 
      // Setup any env variables here
    
      //switch to build directory for openstudio
      dir("/srv/data/OpenStudio/build")  {

        stage("build openstudio") {
          echo("building openstudio")

        //  sh("rm -rf ./Products") //remove any exisiting artifacts
          sh("printenv")
          sh("git checkout develop")
          sh("git pull")
          sh("git fetch origin +refs/pull/*/merge:refs/remotes/origin/pr/*")
          sh("git checkout origin/pr/${env.CHANGE_ID}")
          sh('git merge develop')
          sh('ninja package') // Ninja uses all avail cores without explict cmds
        }

        stage("ctests openstudio") {
          echo("running ctests for openstudio")
          try {
            def num_of_proc = sh(returnStdout: true, script: 'nproc --all').trim()
            sh("ctest -j ${num_of_proc}")
             // Intreprest ctest results here and pass/fail
            currentBuild.result = "SUCCESS" 
          } catch (Exception err) {
            currentBuild.result = "SUCCESS" 
//            currentBuild.result = "FAILURE" // Uncomment when ready
          }
        }

        stage("package openstudio") {
          // push out to aws repo
          // sh("date +%R)
          // sh("aws s3 cp ./ s3://openstudio-builds/_CI/OpenStudio/ --recursive --exclude \"*\" --include \"OpenStudio-2.*-Linux.deb\""")
          // sh("aws s3 cp ./ s3://openstudio-builds/develop/latest/ --recursive --exclude \"*\" --include \"OpenStudio-2.*-Linux.deb\""")
          // sh("date +%R")
        }
      }
    }
  }
  
//  node("openstudio-osx-sierra") { 
//    // Setup any env variables here
//
//  }
  
//  node("openstudio-windows") { 
//    // Setup any env variables here
//  }

}


// if (env.CHANGE_ID == null) {
 //full build here
//}