from device.models import Device


class DeviceManager:
    device_cache = {}
    @classmethod
    def get_device(cls, device_id: str) -> Device:
        device = cls.device_cache.get(device_id)
        if device is not None:
            return device
        device = Device.objects.filter(device_id=device_id).first()
        if device is None:
            device = Device.objects.create(device_id=device_id, name=device_id)
        cls.device_cache[device_id] = device
        return device
    

    @classmethod
    def clear_cache(cls):
        cls.device_cache.clear()


    @classmethod
    def remove_device(cls, device_id: str):
        cls.device_cache.pop(device_id, None)