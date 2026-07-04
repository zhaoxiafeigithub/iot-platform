import uuid

from django.db import models

# Create your models here.


class Device(models.Model):
    device_id = models.CharField(max_length=64, unique=True)
    name = models.CharField(max_length=100)
    online = models.BooleanField(default=True)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)
    is_delete = models.BooleanField(default=False)

    def __str__(self):
        return self.device_id


class TemperatureData(models.Model):
    device = models.ForeignKey(Device, on_delete=models.CASCADE)
    temperature = models.FloatField()
    is_delete = models.BooleanField(default=False)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    # def __str__(self):
    #     return self.temperature









