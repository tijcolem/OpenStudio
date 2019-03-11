// Jenkins Pipline (Scripted)
/*
Blocks below setup the incremental builds for ubuntu, osx, and windows on resptive remote 
slave VM nodes according the label tags. Go to Manage Jenkins->Nodes for full node details. 
The CHANGE_ID env is only set for git pull requests so this is good to control the pipeline to 
either buld pull requests as incremental builds vs nightly and on-demand full builds. 

remove comment. 
*/


// Incremental builds for PR and target branch develop
if ((env.CHANGE_ID) && (env.CHANGE_TARGET) ) { // check if set

  if ( env.CHANGE_TARGET == "develop") {

    parallel (  "linux":  { 

      node("openstudio_ubuntu_1604_incr") { 
        // Setup any env variables here

        if (fileExists("/srv/jenkins/openstudio/git/develop/build") == "false") { 
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
            sh("cmake -DOPENSSL_INCLUDE_DIR=/usr/bin/openssl -DBUILD_TESTING=ON -DBUILD_DVIEW=ON -DBUILD_OS_APP=ON -DBUILD_PACKAGE=ON -DBUILD_PAT=OFF -DCMAKE_BUILD_TYPE=Release -DCPACK_BINARY_DEB=ON -            DCPACK_BINARY_IFW=OFF -DCPACK_BINARY_NSIS=OFF -DCPACK_BINARY_RPM=OFF -DCPACK_BINARY_STGZ=OFF -DCPACK_BINARY_TBZ2=OFF -DCPACK_BINARY_TGZ=OFF -DCPACK_BINARY_TXZ=OFF -DCPACK_BINARY_TZ=OFF ../openstudiocore")
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

      node("openstudio_windows_server_2019-vs2013_incr") { 
        // Setup any env variables here
    
        if (fileExists("D:/jenkins/openstudio/develop/build") == "false") { 
          powershell("mkdir D:/jenkins/openstudio/develop/build") 
        }

        //switch to build directory for openstudio
        dir("D:/jenkins/openstudio/develop/build")  {

          stage("build openstudio") {
            echo("building openstudio")
  
          //  sh("rm -rf ./Products") //remove any exisiting artifacts
            powershell("gci env:")
            powershell("git checkout develop")
            powershell("git pull")
            powershell("git fetch origin +refs/pull/*/merge:refs/remotes/origin/pr/*")
            powershell("git checkout origin/pr/${env.CHANGE_ID}")
            powershell("git merge develop")
            powershell("cmake -DBUILD_CSHARP_BINDINGS=ON -DBUILD_DOCUMENTATION=ON -DBUILD_TESTING=ON -DBUILD_DVIEW=ON -DBUILD_OS_APP=ON -DBUILD_PACKAGE=ON -DBUILD_PAT=OFF -DCMAKE_BUILD_TYPE=Release -DCPACK_BINARY_DEB=OFF -DCPACK_BINARY_IFW=ON -DCPACK_BINARY_NSIS=OFF -DCPACK_BINARY_RPM=OFF -DCPACK_BINARY_STGZ=OFF -DCPACK_BINARY_TBZ2=OFF -DCPACK_BINARY_TGZ=OFF -DCPACK_BINARY_TXZ=OFF -DCPACK_BINARY_TZ=OFF  ../openstudiocore") 
            powershell("cmake --build . --config Release --target ALL_BUILD")
            powershell("cmake --build . --config Release --target PACKAGE")
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



  // Incremental builds for PR and target branch develop3
  if ( env.CHANGE_TARGET == "develop3") {

    parallel (  "linux":  { 

      node("openstudio_ubuntu_1804_incr") { 
        // Setup any env variables here

        if (fileExists("/srv/jenkins/openstudio/git/develop3/build") == "false") { 
          sh("mkdir -p /srv/jenkins/openstudio/git/develop3/build") 
        }

        //switch to build directory for openstudio
        dir("/srv/jenkins/openstudio/git/develop3/build")  {

            
          stage("build openstudio") {
            echo("building openstudio")

          //  sh("rm -rf ./Products") //remove any exisiting artifacts
            sh("printenv")
            sh("git checkout develop3")
            sh("git pull")
            sh("git fetch origin +refs/pull/*/merge:refs/remotes/origin/pr/*")
            sh("git checkout origin/pr/${env.CHANGE_ID}")
            sh("git merge develop3")
            sh("cmake -DOPENSSL_INCLUDE_DIR=/usr/bin/openssl -DBUILD_TESTING=ON -DBUILD_DVIEW=ON -DBUILD_OS_APP=ON -DBUILD_PACKAGE=ON -DBUILD_PAT=OFF -DCMAKE_BUILD_TYPE=Release -DCPACK_BINARY_DEB=ON -            DCPACK_BINARY_IFW=OFF -DCPACK_BINARY_NSIS=OFF -DCPACK_BINARY_RPM=OFF -DCPACK_BINARY_STGZ=OFF -DCPACK_BINARY_TBZ2=OFF -DCPACK_BINARY_TGZ=OFF -DCPACK_BINARY_TXZ=OFF -DCPACK_BINARY_TZ=OFF ../openstudiocore")
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

      node("openstudio_windows_server_2019-vs2017_incr") { 
        // Setup any env variables here
    
        if (fileExists("D:/jenkins/openstudio/develop3/build") == "false") { 
          powershell("mkdir D:/jenkins/openstudio/develop3/build") 
        }

        //switch to build directory for openstudio
        dir("D:/jenkins/openstudio/develop/build")  {

          stage("build openstudio") {
            echo("building openstudio")
  
          //  sh("rm -rf ./Products") //remove any exisiting artifacts
            powershell("git checkout develop3")
            powershell("git pull")
            powershell("git fetch origin +refs/pull/*/merge:refs/remotes/origin/pr/*")
            powershell("git checkout origin/pr/${env.CHANGE_ID}")
            powershell("git merge develop3")
            powershell("cmake -DBUILD_CSHARP_BINDINGS=ON -DBUILD_DOCUMENTATION=ON -DBUILD_TESTING=ON -DBUILD_DVIEW=ON -DBUILD_OS_APP=ON -DBUILD_PACKAGE=ON -DBUILD_PAT=OFF -DCMAKE_BUILD_TYPE=Release -DCPACK_BINARY_DEB=OFF -DCPACK_BINARY_IFW=ON -DCPACK_BINARY_NSIS=OFF -DCPACK_BINARY_RPM=OFF -DCPACK_BINARY_STGZ=OFF -DCPACK_BINARY_TBZ2=OFF -DCPACK_BINARY_TGZ=OFF -DCPACK_BINARY_TXZ=OFF -DCPACK_BINARY_TZ=OFF  ../openstudiocore") 
            //powershell("cmake --build . --config Release --target ALL_BUILD")
            powershell("cmake --build . --config Release --target PACKAGE")
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

  else { 
 
    if(env.BRANCH_NAME == 'develop') { 
 
      node("openstudio_ubuntu_1604_full") { 
        // Setup any env variables here

        if (fileExists("/srv/jenkins/openstudio/git") == "false") { 
          sh("mkdir -p /srv/jenkins/openstudio/git") 
        }

        //switch to build directory for openstudio
        dir("/srv/jenkins/openstudio/git")  {

            
          stage("build openstudio") {
            echo("building openstudio")

            sh("git clone --single-branch --branch develop https://github.com/NREL/OpenStudio.git OpenStudio")
  
            if (fileExists("/srv/jenkins/openstudio/git/OpenStudio/build") == "false") { 
              sh("mkdir -p /srv/jenkins/openstudio/git/OpenStudio/build") 
            }
            sh("cd OpenStudio/build")
            sh("cmake -DBUILD_TESTING=ON -DBUILD_DVIEW=ON -DBUILD_OS_APP=ON -DBUILD_PACKAGE=ON -DBUILD_PAT=OFF -DCMAKE_BUILD_TYPE=Release -DCPACK_BINARY_DEB=ON -            DCPACK_BINARY_IFW=OFF -DCPACK_BINARY_NSIS=OFF -DCPACK_BINARY_RPM=OFF -DCPACK_BINARY_STGZ=OFF -DCPACK_BINARY_TBZ2=OFF -DCPACK_BINARY_TGZ=OFF -DCPACK_BINARY_TXZ=OFF -DCPACK_BINARY_TZ=OFF ../openstudiocore")
            sh("make -j 72 package") 
          }

          stage("ctests openstudio") {
            echo("running ctests for openstudio")
            try {
        
                sh("ctest -j 72")
               // Intreprest ctest results here and pass/fail
              currentBuild.result = "SUCCESS" 
            } catch (Exception err) {
              currentBuild.result = "SUCCESS" 
              currentBuild.result = "FAILURE" // Uncomment when ready
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
      } // end node




      
    }


  }



}       //close conditional



//  node("openstudio-osx-sierra") { 
//    // Setup any env variables here
//
//  }
