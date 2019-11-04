module.exports = {
    printWidth: 80,
    tabWidth: 4,
    useTabs: false,
    singleQuote: false,
    semi: true,
    trailingComma: "none",
    bracketSpacing: true,
    overrides: [
        {
            files: "*.js",
            options: {
                parser: "babel"
            }
        },
        {
            files: ["*.css", "*.scss"],
            options: {
                parser: "css"
            }
        }
    ]
};
