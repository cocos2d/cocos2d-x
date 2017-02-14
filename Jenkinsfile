properties properties: [[$class       : 'GithubProjectProperty',
                         displayName  : 'Cocos2d-x',
                         projectUrlStr: 'https://github.com/mbergumi/cocos2d-x/'],
                        [$class         : 'RebuildSettings',
                         autoRebuild    : false,
                         rebuildDisabled: false],
                        pipelineTriggers([])]
                        
stage('draft') {
    parallel linux: {
        node('linux') {
            echo 'Linux build here soon'
        }
    },
    windows: {
        node('windows') {
            echo 'Windows build here soon'
        }
    }
}
