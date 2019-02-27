// Jenkins Pipline (Scripted)
/*
Blocks below setup the incremental builds for ubuntu, osx, and windows on resptive remote 
slave VM nodes according the label tags. Go to Manage Jenkins->Nodes for full node details. 
The CHANGE_ID env is only set for git pull requests so this is good to control the pipeline to 
either buld pull requests as incremental builds vs nightly and on-demand full builds. 
*/


// Build for PR and target branch develop
if ((env.CHANGE_ID) && (env.CHANGE_TARGET) ) { // check if set

  if ( env.CHANGE_TARGET == "develop") {

    parallel (  "linux":  { 

      node("openstudio_ubuntu_1604") { 
        // Setup any env variables here

        if (("/srv/jenkins/openstudio/git/develop/build") == "false") { 
          sh("mkdir -p /srv/jenkins/openstudio/git/develop/build") 
        }

        //switch to build directory for openstudio
        dir("/srv/jenkins/openstudio/git/develop/build")  {

            
          stage("build openstudio") {
            echo("building openstudio")

          //  sh("rm -rf ./Products") //remove any exisiting artifacts
            sh("printenv")
            sh("git checkout develop")
            sh("git pull")
            sh("git fetch origin +refs/pull/*/merge:refs/remotes/origin/pr/*")
            sh("git checkout origin/pr/${env.CHANGE_ID}")
            sh("git merge develop")
            sh("cmake -DOPENSSL_INCLUDE_DIR=/usr/bin/openssl -DBUILD_TESTING=ON -DBUILD_DVIEW=ON -DBUILD_OS_APP=ON -DBUILD_PACKAGE=ON -DBUILD_PAT=OFF -DCMAKE_BUILD_TYPE=Release -DCPACK_BINARY_DEB=ON -            DCPACK_BINARY_IFW=OFF -DCPACK_BINARY_NSIS=OFF -DCPACK_BINARY_RPM=OFF -DCPACK_BINARY_STGZ=OFF -DCPACK_BINARY_TBZ2=OFF -DCPACK_BINARY_TGZ=OFF -DCPACK_BINARY_TXZ=OFF -DCPACK_BINARY_TZ=OFF ../openstudiocore"
            sh("make -j 16 package") // Ninja uses all avail cores without explict cmds
          }

          stage("ctests openstudio") {
            echo("running ctests for openstudio")
//            try {
//              def num_of_proc = sh(returnStdout: true, script: 'nproc --all').trim()
//              sh("ctest -j ${num_of_proc}")
//               // Intreprest ctest results here and pass/fail
//              currentBuild.result = "SUCCESS" 
//            } catch (Exception err) {
//              currentBuild.result = "SUCCESS" 
//              currentBuild.result = "FAILURE" // Uncomment when ready
//           }
          }

          stage("package openstudio") {
            // push out to aws repo
            // sh("date +%R)
            // sh("aws s3 cp ./ s3://openstudio-builds/_CI/OpenStudio/ --recursive --exclude \"*\" --include \"OpenStudio-2.*-Linux.deb\""")
            // sh("aws s3 cp ./ s3://openstudio-builds/develop/latest/ --recursive --exclude \"*\" --include \"OpenStudio-2.*-Linux.deb\""")
            // sh("date +%R")
          }


        }
      } // end node
    },  // next parrell

    "windows": { 

      node("openstudio_windows_server_2019") { 
        // Setup any env variables here
    
        //switch to build directory for openstudio
        dir("D:/Jenkins/OpenStudio")  {

          stage("build openstudio") {
            echo("building openstudio")
  
          //  sh("rm -rf ./Products") //remove any exisiting artifacts
            powershell("gci env:")
            powershell("git checkout develop")
            powershell("git pull")
            powershell("git fetch origin +refs/pull/*/merge:refs/remotes/origin/pr/*")
            powershell("git checkout origin/pr/${env.CHANGE_ID}")
            powershell('git merge develop')
           // sh('ninja package') // Ninja uses all avail cores without explict cmds
          }
        
          stage("ctests openstudio") {
            echo("running ctests for openstudio")
//          try {
//            def num_of_proc = sh(returnStdout: true, script: 'nproc --all').trim()
//            sh("ctest -j ${num_of_proc}")
//            //Intreprest ctest results here and pass/fail
//             currentBuild.result = "SUCCESS" 
//           } catch (Exception err) {
//             currentBuild.result = "SUCCESS" 
//             currentBuild.result = "FAILURE" // Uncomment when ready
          }
  
          stage("package openstudio") {
            // push out to aws repo
            // sh("date +%R)
            // sh("aws s3 cp ./ s3://openstudio-builds/_CI/OpenStudio/ --recursive --exclude \"*\" --include \"OpenStudio-2.*-Linux.deb\""")
            // sh("aws s3 cp ./ s3://openstudio-builds/develop/latest/ --recursive --exclude \"*\" --include \"OpenStudio-2.*-Linux.deb\""")
            // sh("date +%R")
          } 

        } //close directory

      }  // close node 
    })  // close windows and end parrell
  }      //close conditional 
}       //close conditional



//  node("openstudio-osx-sierra") { 
//    // Setup any env variables here
//
//  }
