properties properties: [[$class       : 'GithubProjectProperty',
                         displayName  : 'Cocos2d-x',
                         projectUrlStr: 'https://github.com/mbergumi/cocos2d-x/'],
                        [$class         : 'RebuildSettings',
                         autoRebuild    : false,
                         rebuildDisabled: false],
                        pipelineTriggers([])]

pipeline {
  agent none
  
  stages {
  
    stage("Build") {
      
      steps {
        parallel (
          
          "windows" : {
            
            node('windows') {
              bat "print from windows"    
            }
          },
          
          "linux" : {
            
            node('linux') {
              sh "echo from linux"    
            }
          }                
      )
    }
  }    
}
