
// return to dashboard without
function toDashboard()
{
    window.location.replace("192.168.4.1/");
}

function setTime()
{
    // TODO:
    // - get elements of HTML site
    // - convert to millis
    // - confirmation and redirect


    // 86400000ms = 1day

    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://192.168.4.1/sync', true);
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.send('sync=' + date.toString);

    
    if (!change && xhr.status == 200) {
        
        window.alert("Time synchronized successfully");
    } else if (!change) {
        window.alert("Error synchronizing time");
    }
}


