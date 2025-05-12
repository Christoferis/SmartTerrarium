// this script should do the following:
// it updates the page every few seconds
// it sends a sync task to host when pressing on sync button
// it sends a sync task and redirects to timeset.html when pressing the set time button

//TODO: synchronize on connect

function sync(change)
{
    var date = new Date();
    var ms = (date.getTime() - date.getTimezoneOffset() * 60000) % 86400000;

    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://192.168.4.1/timeset', true);
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.send('sync=' + ms.toString());

    
    if (!change && xhr.status == 200) {
        
        window.alert("Time synchronized successfully");
    } else if (!change) {
        window.alert("Error synchronizing time");
    }
}

function timechange()
{
    sync(true);
    window.location.replace("192.168.4.1/timeedit");
}

// pollux labs
function refresh(refreshPeriod) 
{
    setTimeout('location.reload(true)', refreshPeriod);
}

window.onload = refresh(5000);