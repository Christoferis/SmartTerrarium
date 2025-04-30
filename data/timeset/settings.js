
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

    //in ms
    morning = document.getElementById("morninghours").value * 3600000 + document.getElementById("morningminutes").value * 60000
    evening = document.getElementById("eveninghours").value * 3600000 + document.getElementById("eveningminutes").value * 60000

    console.log(morning);

    date = Date.now();

    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://192.168.4.1/timeset', true);
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.send('sync=' + date.toString());
    xhr.send('morning=' + morning.toString());
    xhr.send('evening=' + evening.toString());

    
    if (!change && xhr.status == 200) {
        
        window.alert("Time synchronized successfully");
    } else if (!change) {
        window.alert("Error synchronizing time");
    }
}


