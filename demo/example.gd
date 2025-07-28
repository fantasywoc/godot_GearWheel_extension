extends Node

# 输入点数组
var points = [
	Vector2(1, 2), 
	Vector2(3, 4), 
	Vector2(5, 6)
]

func _ready() -> void:
	pass
	if ClassDB.class_exists("RotatableRigidBody"):
		print("RotatableRigidBody 插件已正确安装")
		#var example := ExampleClass.new()
		#example.print_type(example)
		## 调用函数并打印结果
		#var doubled = example.double_points(points)
		#print(doubled)  # 输出: [ (2,4), (6,8), (10,12) ]
		## 调用方法...
	else:
		print("RotatableRigidBodyv 未找到，请确保插件已正确安装")
