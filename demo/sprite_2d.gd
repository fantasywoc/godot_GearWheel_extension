extends Sprite2D

@export var border_color: Color = Color(1, 0, 0)       # 边框颜色
@export var border_width: float = 5.0                 # 边框宽度

var polygon_points: PackedVector2Array = []
var line_node: Line2D
var last_parent_transform: Transform2D = Transform2D.IDENTITY

func _ready():
	# 确保父节点是 CollisionPolygon2D
	if not get_parent() is CollisionPolygon2D:
		push_error("Parent node must be a CollisionPolygon2D")
		return
	
	# 创建 Line2D 节点
	line_node = Line2D.new()
	line_node.width = border_width
	line_node.default_color = border_color
	line_node.closed = true
	add_child(line_node)
	
	# 记录初始变换
	last_parent_transform = get_parent().transform
	
	# 获取多边形点
	update_polygon()
	
	# 监听多边形变化
	get_parent().connect("polygon_changed", Callable(self, "_on_polygon_changed"))

func _process(_delta):
	# 检查父节点变换是否变化
	if get_parent().transform != last_parent_transform:
		update_polygon()
		last_parent_transform = get_parent().transform

func _on_polygon_changed():
	update_polygon()

func update_polygon():
	# 获取父节点的多边形点
	var parent = get_parent() as CollisionPolygon2D
	polygon_points = parent.polygon
	
	# 如果没有点，使用默认矩形
	if polygon_points.size() == 0:
		polygon_points = PackedVector2Array([
			Vector2(-50, -50),
			Vector2(50, -50),
			Vector2(50, 50),
			Vector2(-50, 50)
		])
	
	# 应用父节点变换
	var transformed_points = apply_parent_transform(polygon_points)
	
	# 更新 Line2D 的点
	line_node.points = transformed_points

# 修复：正确应用父节点变换，将点转换到当前节点的坐标空间
func apply_parent_transform(points: PackedVector2Array) -> PackedVector2Array:
	var transformed_points = PackedVector2Array()
	var parent = get_parent()
	
	for point in points:
		# 将点从父节点的本地坐标转换到当前节点的坐标空间
		# 这会正确处理所有缩放、旋转和位置变换
		transformed_points.append(to_local(parent.to_global(point)))
	
	return transformed_points
