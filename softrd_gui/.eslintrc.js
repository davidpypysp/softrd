module.exports = {
    parser: "babel-eslint",
    parserOptions: {
        ecmaVersion: 6,
        sourceType: "module",
        ecmaFeatures: {
            jsx: true,
            modules: true
        }
    },
    rules: {
        // Require a semi colon at the end of a statement.
        semi: ["error", "always"],
        // Maximum line length is 80.
        "max-len": ["error", 80],
        // Always require curly brackets.
        curly: "error",

        // Require the use of `===` and `!==`.
        eqeqeq: "error",
        // Disallow the use of `eval()`.
        "no-eval": "error",
        // Every `async` function should have `await`.
        "require-await": "error",
        // Yoda style, do not do, we, here.
        yoda: "error",
        // Disallow variable declarations from shadowing variables
        // declared in the outer scope.
        "no-shadow": "error",
        // Require initialization in variable declaration.
        "init-declarations": ["error", "always"],
        // Disallow unused variables.
        // TODO(breakds): Re-disallow when the repo is more stable.
        // "no-unused-vars": "error",
        // Require constructor names to begin with a capital letter.
        "new-cap": [
            "error",
            {
                newIsCap: true,
                capIsNew: false
            }
        ],
        // Require parentheses when invoking a constructor with no
        // arguments.
        "new-parens": "error",
        // Disallow trailing white space at the end of lines.
        "no-trailing-spaces": "error",
        // React specific rule. Enable this so that no-unused-vars respect
        // the use of a react component.
        "react/jsx-uses-vars": "error",
        // Enforce consistent spacing before and after the arrow in arrow
        // functions.
        "arrow-spacing": "error",
        // Disallow reassigning `const` variables.
        "no-const-assign": "error",
        // Disallow unecessary constructors.
        "no-useless-constructor": "warn",
        // Require `let` or `const` instead of `var`.
        "no-var": "error",
        // Require `const` declaration for variables taht are never
        // reassigned after declared.
        "prefer-const": "error",
        indent: ["warn", 4],
        "prettier/prettier": "error"
    },
    plugins: ["prettier", "react"]
};
