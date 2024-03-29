window.addEventListener('DOMContentLoaded', function() {
    var NUM_MOTOR = 4;
    var inputElements = {
        information: {
            configName: document.querySelector("input[name='configName']"),
            configVersion: document.querySelectorAll("input[name='configVersion']"),
            targetProduct: document.querySelector("input[name='targetProduct']")
        },
        network: {
            myIp: document.querySelectorAll("input[name='myIp']"),
            isMyIpAddId: document.querySelector("input[name='isMyIpAddId']"),
            destIp: document.querySelectorAll("input[name='destIp']"),
            dns: document.querySelectorAll("input[name='dns']"),
            gateway: document.querySelectorAll("input[name='gateway']"),
            subnet: document.querySelectorAll("input[name='subnet']"),
            inPort: document.querySelector("input[name='inPort']"),
            outPort: document.querySelector("input[name='outPort']"),
            isOutPortAddId: document.querySelector("input[name='isOutPortAddId']"),
            mac: document.querySelectorAll("input[name='mac']"),
            isMacAddId: document.querySelector("input[name='isMacAddId']"),
            bootedMsgEnable: document.querySelector("input[name='bootedMsgEnable']"),
            canSendMsgBeforeDestIp: document.querySelector("input[name='canSendMsgBeforeDestIp']"),
            reportError: document.querySelector("input[name='reportError']")
        }, 
        alarmAndReport: {
            reportBUSY: document.querySelectorAll("input[name='reportBUSY']"),
            reportHiZ: document.querySelectorAll("input[name='reportHiZ']"),
            reportHomeSwStatus: document.querySelectorAll("input[name='reportHomeSwStatus']"),
            reportLimitSwStatus: document.querySelectorAll("input[name='reportLimitSwStatus']"),
            reportDir: document.querySelectorAll("input[name='reportDir']"),
            reportMotorStatus: document.querySelectorAll("input[name='reportMotorStatus']"),
            reportSwEvn: document.querySelectorAll("input[name='reportSwEvn']"),
            reportUVLO: document.querySelectorAll("input[name='reportUVLO']"),
            reportThermalStatus: document.querySelectorAll("input[name='reportThermalStatus']"),
            reportOCD: document.querySelectorAll("input[name='reportOCD']"),
            reportStall: document.querySelectorAll("input[name='reportStall']"),
            reportPositionInterval: document.querySelectorAll("input[name='reportPositionInterval']"),
            reportPositionListInterval: document.querySelector("input[name='reportPositionListInterval']"),
            OCThreshold: document.querySelectorAll("select[name='OCThreshold']")
        }, 
        driverSettings: {
            homingAtStartup : document.querySelectorAll("input[name='homingAtStartup']"),
            homingDirection : document.querySelectorAll("select[name='homingDirection']"),
            homingSpeed: document.querySelectorAll("input[name='homingSpeed']"),
            homeSwMode: document.querySelectorAll("input[name='homeSwMode']"),
            prohibitMotionOnHomeSw: document.querySelectorAll("input[name='prohibitMotionOnHomeSw']"),
            limitSwMode: document.querySelectorAll("input[name='limitSwMode']"),
            prohibitMotionOnLimitSw: document.querySelectorAll("input[name='prohibitMotionOnLimitSw']"),
            goUnitlTimeout: document.querySelectorAll("input[name='goUnitlTimeout']"),
            releaseSwTimeout: document.querySelectorAll("input[name='releaseSwTimeout']"),
            stepMode: document.querySelectorAll("select[name='stepMode']"),
            isCurrentMode: document.querySelectorAll("input[name='isCurrentMode']"),
            slewRate: document.querySelectorAll("select[name='slewRate']"),
            electromagnetBrakeEnable: document.querySelectorAll("input[name='electromagnetBrakeEnable']"),
            brakeTransitionDuration: document.querySelectorAll("input[name='brakeTransitionDuration']")
        }, 
        speedProfile: {
            acc: document.querySelectorAll("input[name='acc']"),
            dec: document.querySelectorAll("input[name='dec']"),
            maxSpeed: document.querySelectorAll("input[name='maxSpeed']"),
            fullStepSpeed: document.querySelectorAll("input[name='fullStepSpeed']"),
            minSpeed: document.querySelectorAll("input[name='minSpeed']")
        }, 
        voltageMode: {
            KVAL_HOLD: document.querySelectorAll("input[name='KVAL_HOLD']"),
            KVAL_RUN: document.querySelectorAll("input[name='KVAL_RUN']"),
            KVAL_ACC: document.querySelectorAll("input[name='KVAL_ACC']"),
            KVAL_DEC: document.querySelectorAll("input[name='KVAL_DEC']"),
            INT_SPEED: document.querySelectorAll("input[name='INT_SPEED']"),
            ST_SLP: document.querySelectorAll("input[name='ST_SLP']"),
            FN_SLP_ACC: document.querySelectorAll("input[name='FN_SLP_ACC']"),
            FN_SLP_DEC: document.querySelectorAll("input[name='FN_SLP_DEC']"),
            STALL_TH: document.querySelectorAll("select[name='STALL_TH']"),
            lowSpeedOptimizeEnable: document.querySelectorAll("input[name='lowSpeedOptimizeEnable']"),
            lowSpeedOptimize: document.querySelectorAll("input[name='lowSpeedOptimize']")
        }, 
        currentMode: {
            TVAL_HOLD: document.querySelectorAll("input[name='TVAL_HOLD']"),
            TVAL_RUN: document.querySelectorAll("input[name='TVAL_RUN']"),
            TVAL_ACC: document.querySelectorAll("input[name='TVAL_ACC']"),
            TVAL_DEC: document.querySelectorAll("input[name='TVAL_DEC']"),
            T_FAST: document.querySelectorAll("input[name='T_FAST']"),
            TON_MIN: document.querySelectorAll("input[name='TON_MIN']"),
            TOFF_MIN: document.querySelectorAll("input[name='TOFF_MIN']")
        },
        servoMode: {
            kP: document.querySelectorAll("input[name='kP']"),
            kI: document.querySelectorAll("input[name='kI']"),
            kD: document.querySelectorAll("input[name='kD']")
        }
    };

    var targetAllInputs = {
        alarmAndReport: document.querySelector("input.alarmAndReport[name='targetAll']"),
        driverSettings: document.querySelector("input.driverSettings[name='targetAll']"),
        speedProfile: document.querySelector("input.speedProfile[name='targetAll']"),
        voltageMode: document.querySelector("input.voltageMode[name='targetAll']"),
        currentMode: document.querySelector("input.currentMode[name='targetAll']"),
        servoMode: document.querySelector("input.servoMode[name='targetAll']")
    }
    var rowLabelTexts = {
        alarmAndReport: document.querySelectorAll("div.rowLabel.alarmAndReport p"),
        driverSettings: document.querySelectorAll("div.rowLabel.driverSettings p"),
        speedProfile: document.querySelectorAll("div.rowLabel.speedProfile p"),
        voltageMode: document.querySelectorAll("div.rowLabel.voltageMode p"),
        currentMode: document.querySelectorAll("div.rowLabel.currentMode p"),
        servoMode: document.querySelectorAll("div.rowLabel.servoMode p")
    }

    var form = document.querySelector("form");
    var loadInput = document.querySelector("input[name='load']");

    for (catName in targetAllInputs) {
        targetAllInputs[catName].addEventListener('change', changeTargetAll, false);
        targetAllInputs[catName].dispatchEvent(new Event('change', { 'bubbles': true }));
    }

    function changeTargetAll(e) {
        var catInputs = inputElements[e.target.className];

        for(paramName in catInputs) {
            var paramInputs = catInputs[paramName];
            if (paramInputs.nodeType === undefined) {
                // paramInputs is NodeList
                if(e.target.checked) {
                    paramInputs[0].removeAttribute('disabled');
                    for (var i = 0; i < NUM_MOTOR; i ++) {
                        paramInputs[i + 1].setAttribute('disabled', 'disabled');
                    }
                } else {
                    paramInputs[0].setAttribute('disabled', 'disabled');
                    for (var i = 0; i < NUM_MOTOR; i ++) {
                        paramInputs[i + 1].removeAttribute('disabled');
                    }
                }
            } else {
                // paramInputs is Element
                paramInputs.removeAttribute('disabled');
            }
        }
        if (e.target.checked) {
            rowLabelTexts[e.target.className][0].removeAttribute('disabled');
            for (var i = 0; i < NUM_MOTOR; i ++) {
                rowLabelTexts[e.target.className][i + 1].setAttribute('disabled', 'disabled');
            }
        } else {
            rowLabelTexts[e.target.className][0].setAttribute('disabled', 'disabled');
            for (var i = 0; i < NUM_MOTOR; i ++) {
                rowLabelTexts[e.target.className][i + 1].removeAttribute('disabled');
            }
        }
    }

    form.addEventListener('submit', function(e) {
        e.stopPropagation();
        e.preventDefault();

        var configObject = {};
        for(catName in inputElements) {
            configObject[catName] = {};
            for (paramName in inputElements[catName]) {
                if (catName === 'network' || catName === 'information') {
                    if (0 < inputElements[catName][paramName].length) {
                        configObject[catName][paramName] = [];
                        for (var i = 0; i < inputElements[catName][paramName].length; i++) {
                            configObject[catName][paramName].push(getInputValue(inputElements[catName][paramName][i]));
                        }
                    } else {
                        configObject[catName][paramName] = getInputValue(inputElements[catName][paramName]);
                    }
                } else {
                    var isTargetAll = targetAllInputs[catName].checked;
                    for (paramName in inputElements[catName]) {
                        if (inputElements[catName][paramName].nodeType === undefined) {
                            configObject[catName][paramName] = [];
                            for (var i = 0; i < NUM_MOTOR; i ++) {
                                if (isTargetAll) {
                                    configObject[catName][paramName].push(getInputValue(inputElements[catName][paramName][0]));
                                } else {
                                    configObject[catName][paramName].push(getInputValue(inputElements[catName][paramName][i+1]));
                                }
                            }
                        } else {
                            configObject[catName][paramName] = getInputValue(inputElements[catName][paramName]);
                        }
                    }
                }
            }
        }
        function getInputValue(elm) {
            if (elm.tagName === 'INPUT') {

                var type = elm.getAttribute("type");
                switch (type) {
                    case 'number':
                    return Number(elm.value);
                    break;
                    case 'text':
                    return elm.value;
                    break;
                    case 'checkbox':
                    return elm.checked;
                    break;
                    default:
                    return 0;
                    break;
                }
            } else if (elm.tagName === 'SELECT') {
                return Number(elm.value);
            }
        }


        var configJson = JSON.stringify(configObject, null, '\t');
        var configBlob = new Blob([configJson], {type: 'text/plain'});
        var a = document.createElement('a');
        a.href = URL.createObjectURL(configBlob);
        a.download = 'config.txt';
        a.click();
    }, false);

    loadInput.addEventListener('change', function(e) {
        var fileReader = new FileReader();
        fileReader.readAsText(e.target.files[0]);

        fileReader.onload = function(e) {
            var jsonObject = JSON.parse(e.target.result);
            
            for(catName in inputElements) {
                if (jsonObject[catName] !== undefined) {
                    for (paramName in inputElements[catName]) {
                        if (jsonObject[catName][paramName] !== undefined) {
                            if (catName === 'network' || catName === 'information') {
                                if (0 < inputElements[catName][paramName].length) {
                                    for (var i = 0; i < inputElements[catName][paramName].length; i++) {
                                        setInputValue(inputElements[catName][paramName][i], jsonObject[catName][paramName][i]);
                                    }
                                } else {
                                    setInputValue(inputElements[catName][paramName], jsonObject[catName][paramName]);
                                }
                            } else {
                                for (paramName in inputElements[catName]) {
                                    if (inputElements[catName][paramName].nodeType === undefined) {
                                        for (var i = 0; i < NUM_MOTOR; i ++) {
                                            setInputValue(inputElements[catName][paramName][i+1], jsonObject[catName][paramName][i]);
                                        }
                                    } else {
                                        setInputValue(inputElements[catName][paramName], jsonObject[catName][paramName]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            function setInputValue(elm, val) {
                
                if (elm.tagName === 'INPUT') {

                    var type = elm.getAttribute('type');
                    switch (type) {
                        case 'number':
                        elm.value = val;
                        break;
                        case 'text':
                        elm.value = val;
                        break;
                        case 'checkbox':
                        elm.checked = val;
                        break;
                        default:
                        return 0;
                        break;
                    }
                } else if (elm.tagName === 'SELECT') {
                    elm.selectedIndex = val;
                }
            }
        }

    }, false)
});