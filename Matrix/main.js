const formSize = document.getElementById("form-size")
const formMatrix = document.getElementById("form-matrix")
const divResult = document.getElementById("result")

const inputSize = document.getElementById("input-size")

let size

formSize.addEventListener("submit", (e) => {
    divResult.innerHTML = ""
    formMatrix.style.opacity = "0"
    e.preventDefault();
    window.history.back();
    if (isNaN(+inputSize.value)) {
        alert(inputSize.value + " isn number!")
        throw inputSize.value + " isn number!"
    }
    size = inputSize.value
    const send = `<button id="send"> get answer </button>`
    setTimeout(() => {
        formMatrix.innerHTML = `
                                <section>
                                    ${createMatrix("A", size, size)}
                                     <div class="sing">✖</div>
                                    ${printMatrix(creatMatrixAsk(size))}
                                    <div class="sing">=</div>
                                    ${createMatrix("B", size, 1)}
                                </section>
                                ${send}
                                `
        formMatrix.style.opacity = "1"
    }, 300)
});

formMatrix.addEventListener("submit", (e) => {
    e.preventDefault()
    window.history.back()
    const A = getMatrix("A", size, size)
    const B = getMatrix("B", size, 1)
    divResult.innerHTML = printMatrix(handler(A, B))
})

//UI

function creatMatrixAsk(row) {
    const a = []
    for (let i = 0; i < row; i++) {
        a.push([`X${i}`])
    }
    return a
}

function createMatrix(name, row, col) {
    let a = `<div><div> Matrix ${name.toUpperCase()} </div> <div id="matrix-${name.toLowerCase()}" class="matrix">`
    for (let i = 0; i < row; i++) {
        a += `<div>`
        for (let j = 0; j < col; j++) {
            a += `<input type="text" required/>`
        }
        a += "</div>"
    }
    a += "</div></div>"
    return a
}

function printMatrix(A) {
    let a = "<table class='print matrix'>"
    for (const AElement of A) {
        a += `<tr>`
        for (const AElementElement of AElement) {
            let b = ""
            if (typeof (AElementElement) !== typeof (2))
                b = AElementElement
            else b = AElementElement.toFixed(2)
            a += `<td> ${b} </td>`
        }
        a += `</tr>`
    }
    a += "</table>"
    return a
}

// Input

function getMatrix(name) {
    const matrixBox = document.getElementById(`matrix-${name.toLowerCase()}`)
    const matrix = []
    const rows = matrixBox.getElementsByTagName("div")
    for (const row of rows) {
        const cols = row.getElementsByTagName("input")
        const rowI = []
        for (const col of cols) {
            if (isNaN(+col.value)) {
                alert(col.value + " isn number!")
                throw col.value + " isn number!"
            }
            rowI.push(+col.value)
        }
        matrix.push(rowI)
    }
    return matrix
}


// Algorithm

function UTMatrix(A, B) {
    const size = A.length
    const X = []
    for (let i = size - 1; i >= 0; i--) X.push(0)

    const sumUTM = (num) => {
        let s = 0;
        for (let i = num + 1; i < size; i++) {
            s += A[num][i] * X[i]
        }
        return s
    }
    X[size - 1] = (B[size - 1][0] / A[size - 1][size - 1])
    for (let i = size - 1; i >= 0; i--) {
        X[i] = ((B[i][0] - sumUTM(i)) / A[i][i])
    }
    const r = []
    for (const i of X) {
        const a = [i]
        r.push(a)
    }
    return r
}

function LTMatrix(A, B) {
    const size = A.length
    const X = []
    for (let i = size - 1; i >= 0; i--) X.push(0)

    const sumUTM = (num) => {
        let s = 0;
        for (let i = 0; i < num; i++) {
            s += A[num][i] * X[i]
        }
        return s
    }
    X[0] = (B[0][0] / A[0][0])
    for (let i = 1; i < size; i++) {
        X[i] = ((B[i][0] - sumUTM(i)) / A[i][i])
    }
    const r = []
    for (const i of X) {
        const a = [i]
        r.push(a)
    }
    return r
}

function createLTMatrixAndUTMatrix(A) {
    const result = {
        "UTMatrix": [], "LTMatrix": []
    }

    result.UTMatrix = A
    for (let i = 0; i < A.length; i++) {
        result.LTMatrix.push([])
        for (let j = 0; j < A[i].length; j++) {
            result.LTMatrix[i].push(0);
            if (i === j)
                result.LTMatrix[i][j] = 1
        }
    }

    const act_in_row = (row1, row2, d) => {
        for (let i = 0; i < row1.length; i++) {
            row1[i] += d * row2[i]
        }
    }

    for (let j = 0; j < A.length; j++) {
        for (let i = A.length - 1; i > j; i--) {
            const d = -(A[i][j] / A[j][j])
            act_in_row(A[i], A[j], d)
            result.LTMatrix[i][j] = -d
        }
    }

    return result
}

function handler(A, B) {
    const matrix = createLTMatrixAndUTMatrix(A)
    const r = LTMatrix(matrix.LTMatrix, B)
    return UTMatrix(matrix.UTMatrix, r)
}