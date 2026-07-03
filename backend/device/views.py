import json

from django.db import IntegrityError
from django.shortcuts import render
from django.views.decorators.csrf import csrf_exempt

from device.models import Device, TemperatureData
from utils import result

# Create your views here.


@csrf_exempt
def report_temperature(request):
    if request.method == 'POST':
        data = json.loads(request.body)
        device_id = data.get('deviceId')
        if not device_id:
            return result.error_param("deviceId")
        temperature = data.get('temperature')
        if temperature is None:
            return result.error_param("temperature")
        device = Device.objects.filter(device_id=device_id).first()
        if not device:
            return result.error_msg('设备不存在')
        TemperatureData.objects.create(device=device, temperature=temperature)
        # device.save()
        return result.success_response(data)
    return result.error_request_method()


@csrf_exempt
def register_device(request):
    if request.method != 'POST':
        return result.error_request_method()
    data = json.loads(request.body)
    device_id = data.get('deviceId')
    if not device_id:
        return result.error_param("deviceId")
    try:
        device = Device.objects.create(device_id=device_id)
    except IntegrityError:
        return result.error_msg(
            '设备已存在'
        )
    return result.success_response(device)



