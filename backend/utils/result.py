from django.http import JsonResponse


def error_request_method():
    return JsonResponse({
        'status': 104,
        'msg': '不支持的请求方法'
    })


def error_param(param):
    return JsonResponse({
        'status': 100,
        'msg': f'{param}参数错误'
    })


def error_object_no_exist():
    return JsonResponse({
        'status': 101,
        'msg': '对象不存在'
    })


def error_msg(msg):

    return JsonResponse({
        'status': 102,
        'msg': msg
    })


# def error_access_token_invalidate():
#     return JsonResponse({
#         'status': 106,
#         'msg': 'access_token invalidate'
#     })
#
#
# def error_access_token_expired():
#     return JsonResponse({
#         'status': 105,
#         'msg': 'access_token expired'
#     })


# def mall_error_msg(response):
#     if 'msg' in response:
#         return JsonResponse({
#             'status': 102,
#             'msg': f'mallApi报错,msg:{response["msg"]}'
#         })
#     return JsonResponse({
#         'status': 102,
#         'msg': f'mallApi报错,msg:{response}'
#     })


def success_response(data):
    return JsonResponse({
        'status': 200,
        'data': data,
        'msg': '请求成功'
    })
