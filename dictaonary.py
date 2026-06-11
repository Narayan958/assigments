import copy


products = [
    {"name": "GeometryBox", "stock": 18},
    {"name": "Notebook", "stock": 12},
    {"name": "Pencil", "stock": 8},
    {"name": "Eraser", "stock": 3},
    {"name": "Marker", "stock": 15},
    {"name": "Scale", "stock": 9}
]


product_copy = products[0].copy()
product_copy["stock"] = 20


print("Original first product:")
print(products[0])

print("\nCopied product with updated stock:")
print(product_copy)


print("\nAll products with stock less than 10:")
for p in products:
    if p["stock"] < 10:
        print(f"- {p['name']} (stock: {p['stock']})")