This sample shows how to use AssetsManager to auto-update application resources(pictures or scripts).

In this sample, there is a scene which contains three items:
* enter

    Start to run script.
* reset

    Delete downloaded resources and delete recorded version code.
* update

    Download new version of package if it exits. 

You can use this sample like this:
* Run original version application(refered as v1)

```
start application
click "enter"
```
* Run new version application(v2)

```
start application
click "update"
click "enter"
```
You will find the changes.
* Run v1 again after running v2

```
start application
click "reset"
click "enter"
```
The application turns back to v1. Ofcourse you can run v2 again as mentioned abave.
    
