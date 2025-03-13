#include <stdio.h>
#include <string.h>

// User Details
typedef struct
{
    char userName[30];
    char userPassword[20];
    char role[10]; // "salesman"
} User;

// Product Details
typedef struct
{
    int id;
    char name[50];
    char category[50];
    float costPrice;
    float sellPrice;
    int quantity;
    float totalCostPrice;
} Product;

// Sales info
typedef struct
{
    int productId;
    char productName[50];
    int quantitySold;
    float totalSellPrice;
} Sale;

// Purchase info
typedef struct
{
    int productId;
    char productName[50];
    int quantityBought;
    float totalCostPrice;
} Purchase;

User users[20];
Product products[50];
Sale sales[50];
Purchase purchases[50];

int userCount = 0;
int productCount = 0;
int salesCount = 0;
int purchaseCount = 0;

// Function Prototypes
void saveUsers();
void saveProducts();
void saveSales();
void savePurchases();
void registerUser();
int loginUser();
void viewProducts();
void addProduct();
void deleteProduct();
void searchProduct();
void sellProduct();
void viewPurchaseHistory();

// Save users to file
void saveUsers()
{
    FILE *fptr = fopen("users.txt", "w");
    if (fptr)
    {
        for (int i = 0; i < userCount; i++)
        {
            fprintf(fptr, "Username: %s Password: %s Role: %s\n", users[i].userName, users[i].userPassword, users[i].role);
        }
        fclose(fptr);
    }
}

// Save products to file
void saveProducts()
{
    FILE *fptr = fopen("products.txt", "w");
    if (fptr)
    {
        for (int i = 0; i < productCount; i++)
        {
            fprintf(fptr, "ID: %d Name: %s Category: %s Cost Price: %.2f Sell Price: %.2f Quantity: %d Total Cost: %.2f\n",
                    products[i].id, products[i].name, products[i].category, products[i].costPrice, products[i].sellPrice, products[i].quantity, products[i].totalCostPrice);
        }
        fclose(fptr);
    }
}


// Save sales to file
void saveSales()
{
    FILE *fptr = fopen("sales.txt", "w");
    if (fptr)
    {
        for (int i = 0; i < salesCount; i++)
        {
            fprintf(fptr, "Product ID: %d Name: %s Quantity Sold: %d Total Sell Price: %.2f\n",
                    sales[i].productId, sales[i].productName, sales[i].quantitySold, sales[i].totalSellPrice);
        }
        fclose(fptr);
    }
}

// Save purchases to file
void savePurchases()
{
    FILE *fptr = fopen("purchases.txt", "w");
    if (fptr)
    {
        for (int i = 0; i < purchaseCount; i++)
        {
            fprintf(fptr, "Product ID: %d Name: %s Quantity Bought: %d Total Cost Price: %.2f\n",
                    purchases[i].productId, purchases[i].productName, purchases[i].quantityBought, purchases[i].totalCostPrice);
        }
        fclose(fptr);
    }
}

// Register user as salesman
void registerUser()
{
    if (userCount < 20)
    {
        User newUser;
        getchar(); // To handle newline
        printf("Enter Username: ");
        fgets(newUser.userName, sizeof(newUser.userName), stdin);
        newUser.userName[strcspn(newUser.userName, "\n")] = '\0';

        for (int i = 0; i < userCount; i++)
        {
            if (strcmp(users[i].userName, newUser.userName) == 0)
            {
                printf("Username already exists!\n");
                return;
            }
        }

        printf("Enter Password: ");
        fgets(newUser.userPassword, sizeof(newUser.userPassword), stdin);
        newUser.userPassword[strcspn(newUser.userPassword, "\n")] = '\0';

        strcpy(newUser.role, "salesman");

        users[userCount++] = newUser;
        saveUsers();
        printf("Registration successful!\n");
    }
    else
    {
        printf("User limit reached!\n");
    }
}

// Login user as salesman
int loginUser()
{
    char userName[30], userPassword[20];
    getchar();
    printf("Enter Username: ");
    fgets(userName, sizeof(userName), stdin);
    userName[strcspn(userName, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(userPassword, sizeof(userPassword), stdin);
    userPassword[strcspn(userPassword, "\n")] = '\0';

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].userName, userName) == 0 && strcmp(users[i].userPassword, userPassword) == 0 && strcmp(users[i].role, "salesman") == 0)
        {
            printf("Login successful as salesman!\n");
            return 1;
        }
    }
    printf("Invalid credentials!\n");
    return 0;
}

// View products
void viewProducts()
{
    printf("\nProducts:\n");
    for (int i = 0; i < productCount; i++)
    {
        printf("ID: %d Name: %s Category: %s Cost: %.2f Sell: %.2f Quantity: %d\n",
               products[i].id, products[i].name, products[i].category, products[i].costPrice, products[i].sellPrice, products[i].quantity);
    }
}

// Add product
void addProduct()
{
    if (productCount < 50)
    {
        Product newProduct;
        printf("Enter Product ID: ");
        scanf("%d", &newProduct.id);
        getchar();

        printf("Enter Product Name: ");
        fgets(newProduct.name, sizeof(newProduct.name), stdin);
        newProduct.name[strcspn(newProduct.name, "\n")] = '\0';

        printf("Enter Category: ");
        fgets(newProduct.category, sizeof(newProduct.category), stdin);
        newProduct.category[strcspn(newProduct.category, "\n")] = '\0';

        printf("Enter Cost Price: ");
        scanf("%f", &newProduct.costPrice);

        printf("Enter Sell Price: ");
        scanf("%f", &newProduct.sellPrice);

        printf("Enter Quantity: ");
        scanf("%d", &newProduct.quantity);

        newProduct.totalCostPrice = newProduct.costPrice * newProduct.quantity;

        products[productCount++] = newProduct;

        // Log purchase
        Purchase newPurchase = {newProduct.id, "", newProduct.quantity, newProduct.totalCostPrice};
        strcpy(newPurchase.productName, newProduct.name);
        purchases[purchaseCount++] = newPurchase;

        saveProducts();
        savePurchases();

        printf("Product added successfully!\n");
    }
    else
    {
        printf("Product limit reached!\n");
    }
}

// Delete product
void deleteProduct()
{
    int id, found = 0;
    printf("Enter Product ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
        {
            found = 1;
            for (int j = i; j < productCount - 1; j++)
            {
                products[j] = products[j + 1];
            }
            productCount--;
            saveProducts();
            printf("Product deleted successfully!\n");
            return;
        }
    }
    if (!found)
        printf("Product not found!\n");
}

// Search product
void searchProduct()
{
    char searchName[50];
    printf("Enter Product Name to search: ");
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    for (int i = 0; i < productCount; i++)
    {
        if (strstr(products[i].name, searchName))
        {
            printf("ID: %d Name: %s Category: %s Cost: %.2f Sell: %.2f Quantity: %d\n",
                   products[i].id, products[i].name, products[i].category, products[i].costPrice, products[i].sellPrice, products[i].quantity);
        }
    }
}

// Sell product
// Sell product
void sellProduct()
{
    int id, quantity, found = 0;
    printf("Enter Product ID to sell: ");
    scanf("%d", &id);
    printf("Enter Quantity to sell: ");
    scanf("%d", &quantity);

    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
        {
            found = 1;
            if (products[i].quantity >= quantity)
            {
                products[i].quantity -= quantity;
                float totalSellPrice = products[i].sellPrice * quantity;

                // Update the total cost price after the sale
                products[i].totalCostPrice = products[i].costPrice * products[i].quantity;

                // Log sale
                Sale newSale = {id, "", quantity, totalSellPrice};
                strcpy(newSale.productName, products[i].name);
                sales[salesCount++] = newSale;

                // Save the updated product and sales data
                saveProducts();
                saveSales();

                printf("Sale completed successfully!\n");

                // Save the updated product data to file after the sale
                saveProducts();

            }
            else
            {
                printf("Not enough stock!\n");
            }
            break;
        }
    }

    if (!found)
        printf("Product not found!\n");
}


// View purchase history
void viewPurchaseHistory()
{
    printf("\nPurchase History:\n");
    for (int i = 0; i < purchaseCount; i++)
    {
        printf("Product ID: %d Name: %s Quantity: %d Total Cost Price: %.2f\n",
               purchases[i].productId, purchases[i].productName, purchases[i].quantityBought, purchases[i].totalCostPrice);
    }
}

int main()
{
    // Load data
    FILE *fptr = fopen("users.txt", "r");
    if (fptr)
    {
        while (fscanf(fptr, "Username: %s Password: %s Role: %s\n", users[userCount].userName, users[userCount].userPassword, users[userCount].role) != EOF)
        {
            userCount++;
        }
        fclose(fptr);
    }

    fptr = fopen("products.txt", "r");
    if (fptr)
    {
        while (fscanf(fptr, "ID: %d Name: %s Category: %s Cost Price: %f Sell Price: %f Quantity: %d Total Cost: %f\n",
                      &products[productCount].id, products[productCount].name, products[productCount].category,
                      &products[productCount].costPrice, &products[productCount].sellPrice, &products[productCount].quantity,
                      &products[productCount].totalCostPrice) != EOF)
        {
            productCount++;
        }
        fclose(fptr);
    }

    fptr = fopen("sales.txt", "r");
    if (fptr)
    {
        while (fscanf(fptr, "Product ID: %d Name: %s Quantity Sold: %d Total Sell Price: %f\n",
                      &sales[salesCount].productId, sales[salesCount].productName, &sales[salesCount].quantitySold,
                      &sales[salesCount].totalSellPrice) != EOF)
        {
            salesCount++;
        }
        fclose(fptr);
    }

    fptr = fopen("purchases.txt", "r");
    if (fptr)
    {
        while (fscanf(fptr, "Product ID: %d Name: %s Quantity Bought: %d Total Cost Price: %f\n",
                      &purchases[purchaseCount].productId, purchases[purchaseCount].productName, &purchases[purchaseCount].quantityBought,
                      &purchases[purchaseCount].totalCostPrice) != EOF)
        {
            purchaseCount++;
        }
        fclose(fptr);
    }

    int choice, loggedIn = 0;
    while (1)
    {
        printf("\n1. Register\n2. Login\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            registerUser();
        }
        else if (choice == 2)
        {
            loggedIn = loginUser();
            if (loggedIn)
            {
                // Salesman menu
                while (1)
                {
                    printf("\n1. View Products\n2. Add Product\n3. Delete Product\n4. Search Product\n5. Sell Product\n6. View Purchase History\n7. Logout\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    if (choice == 1) viewProducts();
                    else if (choice == 2) addProduct();
                    else if (choice == 3) deleteProduct();
                    else if (choice == 4) searchProduct();
                    else if (choice == 5) sellProduct();
                    else if (choice == 6) viewPurchaseHistory();
                    else if (choice == 7) break;
                    else printf("Invalid choice\n");
                }
            }
        }
        else if (choice == 3)
        {
            break;
        }
    }

    return 0;
}